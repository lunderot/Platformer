local target = { x = 0, y = 0 }

function cameraUpdate(deltaTime)
	local x, y = GetEntityPosition(GetCameraId())
	local vx, vy = GetEntityVelocity(GetCameraId())

	local xo, vxo = Spring(x, vx, target.x, 0.23, 8*3.14, deltaTime)
	local yo, vyo = Spring(y, vy, target.y, 0.23, 8*3.14, deltaTime)
	SetEntityPosition(GetCameraId(), xo, yo)
	SetEntityVelocity(GetCameraId(), vxo, vyo)
end
addEventHandler("update", cameraUpdate)


function cameraMouse(button, clicks, state, x, y)
	if state == 1 and button == 1 then
		local wx, wy = GetWorldPositionFromScreenPosition(x, y)
		target = { x = wx, y = wy }
	end
end
addEventHandler("mouseButtonEvent", cameraMouse)

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