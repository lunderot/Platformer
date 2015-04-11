function mouseButtonEventHandler(button, clicks, state, x, y)
	print("mouseButtonEvent")
	print("    button: " .. button)
	print("    clicks: " .. clicks)
	print("    state: " .. state)
	print("    x: " .. x)
	print("    y: " .. y)
	print()
end
--addEventHandler("mouseButtonEvent", mouseButtonEventHandler)

function mouseMotionEventHandler(state, x, y, xrel, yrel)
	print("mouseMotionEvent")
	print("    state: " .. state)
	print("    x: " .. x)
	print("    y: " .. y)
	print("    xrel: " .. xrel)
	print("    yrel: " .. yrel)
	print()
end
--addEventHandler("mouseMotionEvent", mouseMotionEventHandler)

function keyboardEventHandler(key, state, repeating)
	print("keyboardEvent")
	print("    key: " .. key)
	print("    state: " .. state)
	print("    repeating: " .. tostring(repeating))
	print("    name: " .. GetKeyNameFromCode(key))
	print()
end
--addEventHandler("keyboardEvent", keyboardEventHandler)

function playerInput(key, state, repeating)
	if state == 1 then
		local xvel = 0
		local yvel = 0

		if key == GetKeyCodeFromName("A") then
			print("Pressed A")
			xvel = -100
		elseif key == GetKeyCodeFromName("D") then
			print("Pressed D")
			xvel = 100
		end
		

		if not repeating then
			if key == GetKeyCodeFromName("W") then
				yvel = -100
			end
			
		end

		local cxvel, cyvel = GetEntityVelocity(0)
		SetEntityVelocity(0, cxvel+xvel, cyvel+yvel)
	end
end
--addEventHandler("keyboardEvent", playerInput)

function cameraUpdate(deltaTime)
	local x,y = GetEntityPosition(0)
	SetEntityPosition(GetCameraId(), x, y)
end
addEventHandler("update", cameraUpdate)

function entityTest(button, clicks, state, x, y)
	if state == 1 then
		local camx, camy = GetEntityPosition(GetCameraId())
		local camw, camh = GetCameraSize();
		local id = AddEntity(0, "tiles/box.png", 30)
		SetEntityPosition(id, GetWorldPositionFromScreenPosition(x, y))
		SetEntityAcceleration(id, 0, 100)
	end
end
addEventHandler("mouseButtonEvent", entityTest)