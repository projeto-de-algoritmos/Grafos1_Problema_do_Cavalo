let module;

let memory = new WebAssembly.Memory({
	initial: 10,
	maximum: 100
});

WebAssembly.instantiateStreaming(fetch("./wasm/a.out.wasm"), {
	env: {
		emscripten_memcpy_big: memory.grow,
		emscripten_resize_heap: memory.grow
	}
})
.then(obj => {
	module = obj.instance.exports;
	memory = obj.instance.exports.memory;
})

function knight_tour() {
	let ptr = module.dfs(0, 0);
	let arr = new Uint8Array(memory.buffer, ptr);
	console.log(arr.slice(0, 64));
	module.wfree(ptr);
}
