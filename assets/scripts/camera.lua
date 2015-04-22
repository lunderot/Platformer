function cameraUpdate(deltaTime)
	local x,y = GetEntityPosition(0)
	SetEntityPosition(GetCameraId(), x, y)
end
addEventHandler("update", cameraUpdate)