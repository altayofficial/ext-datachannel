--TEST--
Two peer connections exchange messages over loopback
--FILE--
<?php
require __DIR__ . '/loopback.inc';

use altay\datachannel\Context;
use altay\datachannel\DataChannel;
use altay\datachannel\PeerConnection;

$a = new Context();
$b = new Context();
$pa = $a->createPeerConnection(["bindAddress" => "127.0.0.1"]);
$pb = $b->createPeerConnection(["bindAddress" => "127.0.0.1"]);

$channel = $pa->createDataChannel("ReliableDataChannel");
$payloads = ["hello", str_repeat("\x00\xff", 30000), ""];
$sent = false;
$remote = null;

[$seenA, $seenB] = loopback($a, $pa, $b, $pb, function(array $seenA, array $seenB) use ($channel, $payloads, &$sent, &$remote) : bool{
	if(!$sent && count(events_of($seenA, Context::EVENT_CHANNEL_OPEN)) > 0){
		foreach($payloads as $payload){
			$channel->send($payload);
		}
		$sent = true;
	}
	return count(events_of($seenB, Context::EVENT_MESSAGE)) >= 3;
});

$opened = events_of($seenB, Context::EVENT_DATA_CHANNEL);
var_dump(count($opened), $opened[0][3] instanceof DataChannel, $opened[0][3]->getLabel());
$messages = events_of($seenB, Context::EVENT_MESSAGE);
var_dump(array_map(fn(array $e) => strlen($e[3]), $messages));
var_dump($messages[0][3] === "hello", $messages[1][3] === $payloads[1], $messages[0][4]);
var_dump($pa->getState() === PeerConnection::STATE_CONNECTED, $pb->getRemoteFingerprint() !== null);
var_dump(is_array($pa->getSelectedCandidatePair()), $opened[0][3]->getPeerConnectionId() === $pb->getId());

$pa->close();
$pb->close();
echo "done\n";
?>
--EXPECT--
int(1)
bool(true)
string(19) "ReliableDataChannel"
array(3) {
  [0]=>
  int(5)
  [1]=>
  int(60000)
  [2]=>
  int(0)
}
bool(true)
bool(true)
bool(false)
bool(true)
bool(true)
bool(true)
bool(true)
done
