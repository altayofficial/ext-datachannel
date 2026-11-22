<?php

use altay\datachannel\Context;
use altay\datachannel\PeerConnection;

/**
 * Connects two peer connections over loopback by passing the signalling between them by hand.
 * Returns the events each side saw, after $until says it's done or the deadline passes.
 *
 * @param \Closure(array, array) : bool $until
 */
function loopback(Context $a, PeerConnection $pa, Context $b, PeerConnection $pb, \Closure $until, float $timeout = 10.0) : array{
	$seenA = [];
	$seenB = [];
	$deadline = microtime(true) + $timeout;
	while(microtime(true) < $deadline){
		foreach($a->poll() as $event){
			$seenA[] = $event;
			if($event[0] === Context::EVENT_LOCAL_DESCRIPTION){
				$pb->setRemoteDescription($event[3], $event[4]);
			}elseif($event[0] === Context::EVENT_LOCAL_CANDIDATE){
				$pb->addRemoteCandidate($event[3], $event[4]);
			}
		}
		foreach($b->poll() as $event){
			$seenB[] = $event;
			if($event[0] === Context::EVENT_LOCAL_DESCRIPTION){
				$pa->setRemoteDescription($event[3], $event[4]);
			}elseif($event[0] === Context::EVENT_LOCAL_CANDIDATE){
				$pa->addRemoteCandidate($event[3], $event[4]);
			}
		}
		if($until($seenA, $seenB)){
			break;
		}
		usleep(2000);
	}
	return [$seenA, $seenB];
}

function events_of(array $events, int $type) : array{
	return array_values(array_filter($events, fn(array $e) => $e[0] === $type));
}
