local eventHandlers = {}

function addEventHandler(id, triggerFunction)
	if not eventHandlers[id] then
		eventHandlers[id] = {}
	end
	eventHandlers[id][#eventHandlers[id]+1] = triggerFunction
end

function triggerEvent(id, ...)
	local listeners = eventHandlers[id]
	if listeners ~= nil then
		for i=1, #listeners do
			listeners[i](...)
		end
	end
end