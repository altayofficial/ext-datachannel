--TEST--
Objects can only come from a Context, and dropping the context before its peers is safe
--FILE--
<?php
use altay\datachannel\Context;
use altay\datachannel\DataChannel;
use altay\datachannel\PeerConnection;

foreach([PeerConnection::class, DataChannel::class] as $class){
	try{
		new $class();
	}catch(\Error $e){
		echo $e->getMessage(), "\n";
	}
}
try{
	clone new Context();
}catch(\Error $e){
	echo $e->getMessage(), "\n";
}
try{
	serialize(new Context());
}catch(\Exception $e){
	echo $e->getMessage(), "\n";
}

$context = new Context();
var_dump($context->poll());
$peer = $context->createPeerConnection();
var_dump($peer->getId(), $peer->getState() === PeerConnection::STATE_NEW, $peer->getRtt(), $peer->getSelectedCandidatePair());
//creating a channel kicks off negotiation and gathering on libdatachannel's threads
$peer->createDataChannel("ReliableDataChannel");

//the peer starts gathering on its own, its callbacks keep firing into a queue nobody owns anymore
unset($context);
usleep(200000);
$peer->close();
var_dump($peer->getState() === PeerConnection::STATE_CLOSED);
unset($peer);
echo "done\n";
?>
--EXPECTF--
Call to private altay\datachannel\PeerConnection::__construct() from global scope
Call to private altay\datachannel\DataChannel::__construct() from global scope
Trying to clone an uncloneable object of class altay\datachannel\Context
Serialization of 'altay\datachannel\Context' is not allowed
array(0) {
}
int(1)
bool(true)
NULL
NULL
bool(true)
done
