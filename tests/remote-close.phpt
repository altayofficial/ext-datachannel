--TEST--
Closing one side is reported on the other
--FILE--
<?php
require __DIR__ . '/loopback.inc';

use altay\datachannel\Context;
use altay\datachannel\PeerConnection;

$a = new Context();
$b = new Context();
$pa = $a->createPeerConnection(["bindAddress" => "127.0.0.1"]);
$pb = $b->createPeerConnection(["bindAddress" => "127.0.0.1"]);
$channel = $pa->createDataChannel("ReliableDataChannel");

$closed = false;
[$seenA, $seenB] = loopback($a, $pa, $b, $pb, function(array $seenA, array $seenB) use ($pa, &$closed) : bool{
	if(!$closed && count(events_of($seenB, Context::EVENT_CHANNEL_OPEN)) + count(events_of($seenB, Context::EVENT_DATA_CHANNEL)) > 0 && count(events_of($seenA, Context::EVENT_CHANNEL_OPEN)) > 0){
		$pa->close();
		$closed = true;
	}
	return count(events_of($seenB, Context::EVENT_CHANNEL_CLOSED)) > 0;
});
var_dump(count(events_of($seenB, Context::EVENT_CHANNEL_CLOSED)));
var_dump($pa->getCloseReason() === PeerConnection::CLOSE_REASON_LOCAL);
$pb->close();
?>
--EXPECT--
int(1)
bool(true)
