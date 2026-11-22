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
final class DataChannel{
	private function __construct(){}

	/**
	 * The ID events about this channel carry.
	 */
	public function getId() : int{}

	public function getPeerConnectionId() : int{}

	public function getLabel() : string{}

	public function getStream() : ?int{}

	public function isOpen() : bool{}

	public function isClosed() : bool{}

	/**
	 * Returns false when the message had to be buffered rather than handed to the transport straight away.
	 *
	 * @throws DataChannelException
	 */
	public function send(string $data) : bool{}

	public function getBufferedAmount() : int{}

	public function setBufferedAmountLowThreshold(int $amount) : void{}

	public function getMaxMessageSize() : int{}

	public function close() : void{}
}
