let module;

let memory = new WebAssembly.Memory({
	initial: 256,
	maximum: 256
});

WebAssembly.instantiateStreaming(fetch("./wasm/a.out.wasm"), {
	env: {
		emscripten_memcpy_big: memory.grow,
		emscripten_resize_heap: memory.grow,
	}
})
.then(obj => {
	module = obj.instance.exports;
	memory = obj.instance.exports.memory;
})

function knight_tour(n) {

	const x = n/8;
	const y = n%8;

	let ptr = module.dfs(x, y);
	let arr = new Uint8Array(memory.buffer, ptr);
	arr = arr.slice(0, 64);
	module.wfree(ptr);
	return arr;
}
