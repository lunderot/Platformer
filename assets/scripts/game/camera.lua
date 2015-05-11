function cameraUpdate(deltaTime)
	local x,y = GetEntityPosition(GetFirstPlayerId())
	SetEntityPosition(GetCameraId(), x, y)
end
addEventHandler("update", cameraUpdate)