<?php

/**
 * @generate-class-entries
 * @generate-legacy-arginfo 80300
 */

namespace altay\datachannel;

/**
 * @strict-properties
 * @not-serializable
 */
final class PeerConnection{
	/** @var int */
	public const STATE_NEW = 0;
	/** @var int */
	public const STATE_CONNECTING = 1;
	/** @var int */
	public const STATE_CONNECTED = 2;
	/** @var int */
	public const STATE_DISCONNECTED = 3;
	/** @var int */
	public const STATE_FAILED = 4;
	/** @var int */
	public const STATE_CLOSED = 5;

	/** @var int */
	public const GATHERING_NEW = 0;
	/** @var int */
	public const GATHERING_IN_PROGRESS = 1;
	/** @var int */
	public const GATHERING_COMPLETE = 2;

	/** @var int */
	public const CLOSE_REASON_NONE = 0;
	/** @var int */
	public const CLOSE_REASON_LOCAL = 1;
	/** @var int */
	public const CLOSE_REASON_REMOTE_SHUTDOWN = 2;
	/** @var int */
	public const CLOSE_REASON_REMOTE_ABORT = 3;
	/** @var int */
	public const CLOSE_REASON_SCTP_TIMEOUT = 4;
	/** @var int */
	public const CLOSE_REASON_ICE_FAILED = 5;
	/** @var int */
	public const CLOSE_REASON_TRANSPORT_FAILED = 6;

	private function __construct(){}

	/**
	 * The ID events about this connection carry.
	 */
	public function getId() : int{}

	/**
	 * @throws DataChannelException
	 */
	public function setRemoteDescription(string $sdp, string $type) : void{}

	/**
	 * Only needed with disableAutoNegotiation, otherwise the description is created as soon as it can be.
	 *
	 * @throws DataChannelException
	 */
	public function setLocalDescription(string $type = "") : void{}

	public function getLocalDescription() : ?string{}

	public function getLocalDescriptionType() : ?string{}

	/**
	 * @throws DataChannelException
	 */
	public function addRemoteCandidate(string $candidate, string $mid = "0") : void{}

	/**
	 * Options: unordered, maxRetransmits, maxPacketLifeTime (milliseconds), negotiated, stream, protocol.
	 *
	 * @param mixed[] $options
	 * @phpstan-param array<string, mixed> $options
	 * @throws DataChannelException
	 */
	public function createDataChannel(string $label, array $options = []) : DataChannel{}

	public function getState() : int{}

	public function getIceState() : int{}

	public function getGatheringState() : int{}

	public function getCloseReason() : int{}

	/**
	 * Round trip time in milliseconds, null until one has been measured.
	 */
	public function getRtt() : ?int{}

	/**
	 * @return array{rtt: int, rto: int, congestionWindow: int, peerReceiveWindow: int, unackedChunks: int, pendingChunks: int, dataTimeouts: int}|null
	 */
	public function getSctpStats() : ?array{}

	/**
	 * The fingerprint of the certificate the remote side presented, like "sha-256 AB:CD:...", or null before DTLS.
	 */
	public function getRemoteFingerprint() : ?string{}

	/**
	 * @return array{local: array{string, int, string}, remote: array{string, int, string}}|null address, port and type of each side
	 */
	public function getSelectedCandidatePair() : ?array{}

	public function getRemoteMaxMessageSize() : int{}

	public function getBytesSent() : int{}

	public function getBytesReceived() : int{}

	public function close() : void{}
}
