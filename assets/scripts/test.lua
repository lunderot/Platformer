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
addEventHandler("keyboardEvent", keyboardEventHandler)

addEventHandler("keyboardEvent",
	function(key, state, repeating)
		if state == 1 and key == GetKeyCodeFromName("A") and not repeating then
			print("Pressed A")
		end
	end
)