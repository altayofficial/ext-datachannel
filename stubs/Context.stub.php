<?php

/**
 * @generate-class-entries
 * @generate-legacy-arginfo 80300
 */

namespace altay\datachannel;

/**
 * Owns the event queue for every peer connection created from it. libdatachannel runs its own threads; anything they
 * report lands in this queue and only reaches PHP when poll() is called, so a Context belongs to the thread that
 * created it.
 *
 * @strict-properties
 * @not-serializable
 */
final class Context{
	/** @var int */
	public const EVENT_STATE = 1;
	/** @var int */
	public const EVENT_ICE_STATE = 2;
	/** @var int */
	public const EVENT_GATHERING_STATE = 3;
	/** @var int */
	public const EVENT_LOCAL_DESCRIPTION = 4;
	/** @var int */
	public const EVENT_LOCAL_CANDIDATE = 5;
	/** @var int */
	public const EVENT_DATA_CHANNEL = 6;
	/** @var int */
	public const EVENT_CHANNEL_OPEN = 7;
	/** @var int */
	public const EVENT_CHANNEL_CLOSED = 8;
	/** @var int */
	public const EVENT_CHANNEL_ERROR = 9;
	/** @var int */
	public const EVENT_MESSAGE = 10;
	/** @var int */
	public const EVENT_BUFFERED_AMOUNT_LOW = 11;
	/** @var int */
	public const EVENT_LOG = 12;

	/** @var int */
	public const LOG_NONE = 0;
	/** @var int */
	public const LOG_FATAL = 1;
	/** @var int */
	public const LOG_ERROR = 2;
	/** @var int */
	public const LOG_WARNING = 3;
	/** @var int */
	public const LOG_INFO = 4;
	/** @var int */
	public const LOG_DEBUG = 5;
	/** @var int */
	public const LOG_VERBOSE = 6;

	public function __construct(){}

	/**
	 * Creates a peer connection whose events are reported by this context.
	 *
	 * Options: iceServers (list of URLs like "stun:host:port" or "turn:user:pass@host:port"), bindAddress,
	 * portRangeBegin, portRangeEnd, enableIceUdpMux, enableIceTcp, relayOnly, disableAutoNegotiation,
	 * certificatePemFile, keyPemFile, keyPemPass, maxMessageSize, mtu.
	 *
	 * @param mixed[] $options
	 * @phpstan-param array<string, mixed> $options
	 */
	public function createPeerConnection(array $options = []) : PeerConnection{}

	/**
	 * Returns everything that happened since the last call, oldest first. Each event is
	 * [type, peer ID, channel ID, value, extra]:
	 *  - STATE, ICE_STATE, GATHERING_STATE: value is the new state
	 *  - LOCAL_DESCRIPTION: value is the SDP, extra its type
	 *  - LOCAL_CANDIDATE: value is the candidate line, extra its mid
	 *  - DATA_CHANNEL: value is the DataChannel the remote side opened
	 *  - CHANNEL_ERROR: value is the error message
	 *  - MESSAGE: value is the payload, extra is true for a text message
	 *  - LOG: value is the message, extra its level; peer and channel IDs are 0
	 *
	 * @return list<array{int, int, int, mixed, mixed}>
	 */
	public function poll() : array{}

	/**
	 * Sets how much libdatachannel logs. Log lines are process-wide and come out of whichever context polls first.
	 */
	public static function setLogLevel(int $level) : void{}
}
