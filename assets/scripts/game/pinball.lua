SetPosition(GetFirstPlayerId(), 390.167, 400)
ApplyForce(GetFirstPlayerId(), 0, 90)


local flipper0 = AddEntity(4, "assets/textures/circle.png", 50)
SetPosition(flipper0, 91.011, 719.5)
ApplyForceOffset(flipper0, 0, 20, 50, 0)

local flipper1 = AddEntity(4, "assets/textures/circle.png", 50)
SetPosition(flipper1, 308.988, 719.5)
ApplyForceOffset(flipper1, 0, -20, 50, 0)


local controls =	{
						reset			= GetKeyCodeFromName("R"),
						leftFlipper		= GetKeyCodeFromName("A"),
						rightFlipper	= GetKeyCodeFromName("D"),
						fire			= GetKeyCodeFromName("W"),
					}

function playerInput(key, state, repeating)
	local id = GetFirstPlayerId()
	if not repeating then
		if key == controls.reset and state == 1 then
			SetPosition(id, 390.167, 400)
			SetVelocity(id, 0, 0)
		end
		if key == controls.leftFlipper and state == 1 then
			ApplyImpulseOffset(flipper0, 0, 1000, 0.05, -50, 0)
		end
		if key == controls.rightFlipper and state == 1 then
			ApplyImpulseOffset(flipper1, 0, -1000, 0.05, -50, 0)
		end
		if key == controls.fire and state == 1 then
			ApplyImpulse(id, 0, -1000, 0.1)
		end
	end
end
addEventHandler("keyboardEvent", playerInput)

local upperLimit = 0.3
local lowerLimit = 1.0


function limitFlipper(deltaTime)
	local flipperAngle0 = GetAngle(flipper0)
	if flipperAngle0 < upperLimit then
		SetAngle(flipper0, upperLimit)
		SetAngularVelocity(flipper0, 0)
	elseif flipperAngle0 > lowerLimit then
		SetAngle(flipper0, lowerLimit)
		ApplyImpulseOffset(flipper0, 0, -30, deltaTime, 50, 0)
	end


	local flipperAngle1 = GetAngle(flipper1)
	if flipperAngle1 > 3.14-upperLimit then
		SetAngle(flipper1, 3.14-upperLimit)
		SetAngularVelocity(flipper1, 0)
	elseif flipperAngle1 < 2.20 then
		SetAngle(flipper1, 2.20)
		ApplyImpulseOffset(flipper1, 0, 30, deltaTime, 50, 0)
	end
end
addEventHandler("update", limitFlipper)


function playerMouse(button, clicks, state, x, y)
	if state == 1 and button == 3 then
		local wx, wy = GetWorldPositionFromScreenPosition(x, y)
		SetPosition(GetFirstPlayerId(), wx, wy)
		SetVelocity(GetFirstPlayerId(), 0, 0)
	end
end
addEventHandler("mouseButtonEvent", playerMouse)