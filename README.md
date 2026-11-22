# ext-datachannel

PHP bindings for [libdatachannel](https://github.com/paullouisageneau/libdatachannel), just enough of it for WebRTC data channels on a server. It's what NetherLib runs NetherNet on.

libdatachannel does ICE, DTLS and SCTP on its own threads. Nothing it reports touches PHP directly: callbacks only push events into the queue of the `Context` the peer connection came from, and the PHP thread that owns that context picks them up with `poll()`.

```php
use altay\datachannel\Context;

$context = new Context();
$peer = $context->createPeerConnection(["bindAddress" => "0.0.0.0", "enableIceUdpMux" => true, "portRangeBegin" => 19133, "portRangeEnd" => 19133]);
$peer->setRemoteDescription($offerSdp, "offer");

while(true){
	foreach($context->poll() as [$type, $peerId, $channelId, $value, $extra]){
		match($type){
			Context::EVENT_LOCAL_DESCRIPTION => sendAnswer($value),
			Context::EVENT_LOCAL_CANDIDATE => sendCandidate($value, $extra),
			Context::EVENT_DATA_CHANNEL => remember($value),
			Context::EVENT_MESSAGE => handle($channelId, $value),
			default => null
		};
	}
	usleep(5000);
}
```

See [the stubs](stubs/) for the full API.

## Building

libdatachannel is pinned as a submodule. Build it statically, then point the extension at its install prefix:

```sh
git submodule update --init --recursive
cmake -S deps/libdatachannel -B build/libdatachannel -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=OFF -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
  -DNO_MEDIA=ON -DNO_WEBSOCKET=ON -DNO_EXAMPLES=ON -DNO_TESTS=ON -DUSE_NICE=OFF -DUSE_NETTLE=OFF \
  -DCMAKE_INSTALL_PREFIX=$PWD/build/prefix
ninja -C build/libdatachannel install

phpize
./configure --with-datachannel=$PWD/build/prefix
make
make test
```

Requires PHP 8.3 or newer, a C++20 compiler, CMake and OpenSSL.

## License

The extension is MIT licensed. libdatachannel, libjuice and usrsctp keep their own licenses (MPL 2.0, MPL 2.0 and BSD 3-clause), see deps/libdatachannel.
