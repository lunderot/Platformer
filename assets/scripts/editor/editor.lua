require "math"

local placeType = 1

local isPlacingLine = false
local line = {}

local tileSize = 70
local tileIndex = 1
local tilesPlaced = {}
local savePath = "assets/maps/"

local markerTexture = "assets/textures/marker.png"

local markerEntity = AddEntity(3, markerTexture, tileSize/2)

function getNearestMultiple(number, multiple)
	return math.floor(number / multiple) * multiple
end

function placeTypeChange(key, state, repeating)
	if state == 1 and not repeating then
		if key == GetKeyCodeFromName("1") then
			placeType = 1
			SetMarkerTexture(markerEntity, markerTexture)
		elseif key == GetKeyCodeFromName("2") then
			isPlacingLine = false
			placeType = 2
			SetMarkerTexture(markerEntity, tiles[tileIndex])
		end
	end
end
addEventHandler("keyboardEvent", placeTypeChange)

function saveMap(key, state, repeating)
	if state == 1 and not repeating then
		if key == GetKeyCodeFromName("F8") then
			SaveToFile(savePath .. os.date("%d-%m-%y %H.%M.map"))
		end
	end
end
addEventHandler("keyboardEvent", saveMap)

function changeTile(key, state, repeating)
	if state == 1 then
		if key == GetKeyCodeFromName("0") then
			if tileIndex == #tiles then
				tileIndex = 1
			else
				tileIndex = tileIndex + 1
			end
		end
		if key == GetKeyCodeFromName("9") then
			if tileIndex == 1 then
				tileIndex = #tiles
			else
				tileIndex = tileIndex - 1
			end
		end
		if placeType == 2 then
			SetMarkerTexture(markerEntity, tiles[tileIndex])
		end
	end
end
addEventHandler("keyboardEvent", changeTile)

function undoHandler(key, state, repeating)
	if state == 1 and not repeating then
		if key == GetKeyCodeFromName("Z") then
			if #tilesPlaced > 0 then
				RemoveEntity(tilesPlaced[#tilesPlaced])
				tilesPlaced[#tilesPlaced] = nil
			end
		end
	end
end
addEventHandler("keyboardEvent", undoHandler)

function mouseButtonEventHandler(button, clicks, state, x, y)
	if state == 1 and clicks == 1 then
		if placeType == 1 then --Place collision line
			if isPlacingLine then
				line.x2, line.y2 = GetWorldPositionFromScreenPosition(x, y)
				print("2: " .. line.x2 .." " .. line.y2)
				line.x1 = getNearestMultiple(line.x1, tileSize) + tileSize / 2
				line.y1 = getNearestMultiple(line.y1, tileSize) + tileSize / 2
				line.x2 = getNearestMultiple(line.x2, tileSize) + tileSize / 2
				line.y2 = getNearestMultiple(line.y2, tileSize) + tileSize / 2
				AddCollisionLine(line.x1, line.y1, line.x2, line.y2)
				isPlacingLine = false
			else
				line.x1, line.y1 = GetWorldPositionFromScreenPosition(x, y)
				print("1: " .. line.x1 .." " .. line.y1)
				isPlacingLine = true
			end
		elseif placeType == 2 then --Place tile
			local tpx, tpy = GetWorldPositionFromScreenPosition(x, y)
			local tilePos = {
								x = getNearestMultiple(tpx + tileSize/2, tileSize),
								y = getNearestMultiple(tpy + tileSize/2, tileSize)
							}
			
			local id = AddEntity(1, tiles[tileIndex], tileSize)
			SetEntityPosition(id, tilePos.x, tilePos.y)
			table.insert(tilesPlaced, id)
		end
	end
end
addEventHandler("mouseButtonEvent", mouseButtonEventHandler)

function editorMouseEvent(state, x, y, xrel, yrel)
	local tpx, tpy = GetWorldPositionFromScreenPosition(x, y)
	local tilePos = {x = 0, y = 0}
	if placeType == 2 then
		tilePos.x = getNearestMultiple(tpx + tileSize/2, tileSize)
		tilePos.y = getNearestMultiple(tpy + tileSize/2, tileSize)
	else
		tilePos.x = getNearestMultiple(tpx, tileSize) + tileSize / 2
		tilePos.y = getNearestMultiple(tpy, tileSize) + tileSize / 2
	end
	SetEntityPosition(markerEntity, tilePos.x, tilePos.y)
end
addEventHandler("mouseMotionEvent", editorMouseEvent)