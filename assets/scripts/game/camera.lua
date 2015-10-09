function cameraMouse(button, clicks, state, x, y)
	if state == 1 and button == 1 then
		local wx, wy = GetWorldPositionFromScreenPosition(x, y)
		SetRenderPosition(GetCameraId(), wx, wy)
	end
end
addEventHandler("mouseButtonEvent", cameraMouse)