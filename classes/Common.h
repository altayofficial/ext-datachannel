#ifndef HAVE_DATACHANNEL_COMMON_H
#define HAVE_DATACHANNEL_COMMON_H

#include <atomic>
#include <deque>
#include <memory>
#include <mutex>
#include <string>

#include <rtc/rtc.hpp>

extern "C" {
#include "php.h"
}

enum EventType : int {
	EVENT_STATE = 1,
	EVENT_ICE_STATE = 2,
	EVENT_GATHERING_STATE = 3,
	EVENT_LOCAL_DESCRIPTION = 4,
	EVENT_LOCAL_CANDIDATE = 5,
	EVENT_DATA_CHANNEL = 6,
	EVENT_CHANNEL_OPEN = 7,
	EVENT_CHANNEL_CLOSED = 8,
	EVENT_CHANNEL_ERROR = 9,
	EVENT_MESSAGE = 10,
	EVENT_BUFFERED_AMOUNT_LOW = 11,
	EVENT_LOG = 12
};

struct QueuedEvent {
	EventType type;
	zend_long peerId = 0;
	zend_long channelId = 0;
	zend_long number = 0;
	bool hasText = false;
	std::string text;
	std::string extra;
	std::shared_ptr<rtc::DataChannel> channel;
};

/*
 * Everything libdatachannel's threads report goes through one of these. Its callbacks only ever push here and never
 * touch the engine, the owning PHP thread drains it in Context::poll(). Callbacks hold it weakly, so a context that
 * is gone simply stops collecting.
 */
struct EventQueue {
	std::mutex mutex;
	std::deque<QueuedEvent> events;
	std::atomic<zend_long> nextChannelId{1};

	void push(QueuedEvent&& event) {
		std::lock_guard<std::mutex> lock(mutex);
		events.push_back(std::move(event));
	}

	std::deque<QueuedEvent> drain() {
		std::deque<QueuedEvent> drained;
		std::lock_guard<std::mutex> lock(mutex);
		drained.swap(events);
		return drained;
	}
};

typedef struct _peer_connection_obj {
	std::shared_ptr<rtc::PeerConnection> connection;
	std::shared_ptr<EventQueue> queue;
	zend_long id;
	zend_object std;
} peer_connection_obj;

typedef struct _data_channel_obj {
	std::shared_ptr<rtc::DataChannel> channel;
	zend_long id;
	zend_long peerId;
	zend_object std;
} data_channel_obj;

extern zend_class_entry* datachannel_exception_ce;
extern zend_class_entry* peer_connection_ce;
extern zend_class_entry* data_channel_ce;

void init_class_Context();
void init_class_PeerConnection();
void init_class_DataChannel();

void log_queue_drain(std::deque<QueuedEvent>& into);

void peer_connection_create(zval* return_value, std::shared_ptr<rtc::PeerConnection> connection, std::shared_ptr<EventQueue> queue, zend_long id);
void data_channel_create(zval* return_value, std::shared_ptr<rtc::DataChannel> channel, zend_long id, zend_long peerId);
void data_channel_attach(const std::shared_ptr<rtc::DataChannel>& channel, const std::shared_ptr<EventQueue>& queue, zend_long peerId, zend_long channelId);

#define DATACHANNEL_TRY try {
#define DATACHANNEL_CATCH \
	} catch (const std::exception& e) { \
		zend_throw_exception(datachannel_exception_ce, e.what(), 0); \
		RETURN_THROWS(); \
	}

#endif
