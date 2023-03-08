#pragma once

class CanvasComponent
{
protected:
	auto CallOnDevice(auto& canvas, auto Func, auto... Args)
	{
		return std::mem_fn(Func)(canvas.Device.Get(), Args...);
	}
};