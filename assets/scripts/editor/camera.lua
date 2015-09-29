local tileSize = 70
local target = { x = 0, y = 0 }

function cameraInput(key, state, repeating)
	local input = { x = 0, y = 0 }
	--if not repeating then
		if key == GetKeyCodeFromName("A") then
			if state == 1 then
				input.x = -tileSize
			else
				input.x = 0
			end
		elseif key == GetKeyCodeFromName("D") then
			if state == 1 then
				input.x = tileSize
			else
				input.x = 0
			end
		end
		if key == GetKeyCodeFromName("W") then
			if state == 1 then
				input.y = -tileSize
			else
				input.y = 0
			end
		elseif key == GetKeyCodeFromName("S") then
			if state == 1 then
				input.y = tileSize
			else
				input.y = 0
			end
		end
		local camx, camy = GetEntityPosition(GetCameraId())
		--SetEntityPosition(GetCameraId(), camx + input.x, camy + input.y)
		target = {x = camx + input.x, y = camy + input.y}
	--end
end
addEventHandler("keyboardEvent", cameraInput)

--  x     - value             (input/output)
--  v     - velocity          (input/output)
--  xt    - target value      (input)
--  zeta  - damping ratio     (input)
--  omega - angular frequency (input)
--  h     - time step         (input)

function Spring(x, v, xt, zeta, omega, h)
	  f = 1.0 + 2.0 * h * zeta * omega;
	  oo = omega * omega;
	  hoo = h * oo;
	  hhoo = h * hoo;
	  detInv = 1.0 / (f + hhoo);
	  detX = f * x + h * v + hhoo * xt;
	  detV = v + hoo * (xt - x);
	  x = detX * detInv;
	  v = detV * detInv;
	  return x, v
end

function cameraUpdate(deltaTime)
	local x, y = GetEntityPosition(GetCameraId())
	local vx, vy = GetEntityVelocity(GetCameraId())

	local xo, vxo = Spring(x, vx, target.x, 0.23, 8*3.14, deltaTime)
	local yo, vyo = Spring(y, vy, target.y, 0.23, 8*3.14, deltaTime)
	SetEntityPosition(GetCameraId(), xo, yo)
	SetEntityVelocity(GetCameraId(), vxo, vyo)
end
addEventHandler("update", cameraUpdate)

