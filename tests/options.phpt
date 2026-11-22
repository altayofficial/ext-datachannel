--TEST--
createPeerConnection() and createDataChannel() validate their options
--FILE--
<?php
use altay\datachannel\Context;

$context = new Context();
foreach([
	["nope" => 1],
	["bindAddress" => 1],
	["portRangeBegin" => 0],
	["portRangeBegin" => 2000, "portRangeEnd" => 1000],
	["iceServers" => "stun:example.com"],
	["iceServers" => [1]],
	["relayOnly" => "yes"],
	[1, 2],
] as $options){
	try{
		$context->createPeerConnection($options);
		echo "no error\n";
	}catch(\TypeError|\ValueError $e){
		echo get_class($e), ": ", $e->getMessage(), "\n";
	}
}

$peer = $context->createPeerConnection(["iceServers" => ["stun:127.0.0.1:3478"], "enableIceUdpMux" => false, "maxMessageSize" => 262144]);
foreach([
	["nope" => true],
	["unordered" => 1],
	["maxRetransmits" => -1],
	["maxRetransmits" => 1, "maxPacketLifeTime" => 1],
] as $options){
	try{
		$peer->createDataChannel("x", $options);
		echo "no error\n";
	}catch(\TypeError|\ValueError $e){
		echo get_class($e), ": ", $e->getMessage(), "\n";
	}
}
$channel = $peer->createDataChannel("UnreliableDataChannel", ["unordered" => true, "maxRetransmits" => 0]);
var_dump($channel->getLabel(), $channel->isOpen());
$peer->close();
?>
--EXPECT--
ValueError: Unknown option "nope"
TypeError: Option "bindAddress" must be of type string, int given
ValueError: Option "portRangeBegin" must be between 1 and 65535
ValueError: Option "portRangeBegin" must not be greater than "portRangeEnd"
TypeError: Option "iceServers" must be of type array, string given
TypeError: Option "iceServers" must be of type string, int given
TypeError: Option "relayOnly" must be of type bool, string given
ValueError: Options must be keyed by name
ValueError: Unknown option "nope"
TypeError: Option "unordered" must be of type bool, int given
ValueError: Option "maxRetransmits" must be an int between 0 and 65535
ValueError: Options "maxRetransmits" and "maxPacketLifeTime" can't be used together
string(21) "UnreliableDataChannel"
bool(false)
