local n_locSpeed = 0.1
local n_locScriptID
local n_locGameObjectID

local n_locState = 0

function Init(n_aScriptID, n_aGameObjectID)
    n_locScriptID = n_aScriptID
    n_locGameObjectID = n_aGameObjectID

    n_locHealth = GetObjectHealth(n_locGameObjectID)
    n_locHealth = 50

    if n_locHealth > 66 then
        n_locState = 0
    elseif n_locHealth < 33 then
        n_locState = 1
    else
        n_locState = 2
    end
end

function SetSpeed(n_aSpeed)
    n_locSpeed = n_aSpeed
end

function Chase()
    local ga = {}
    ga = {GetGameObjects()}

    for index, value in pairs(ga)
    do
        if (value ~= n_locGameObjectID)
        then
            local x1
            local y1

            x1,y1 = GetGameObjectPosition(value)

            local x2
            local y2

            x2, y2 = GetGameObjectPosition(n_locGameObjectID)

            return x1 - x2, y1 - y2
        end
    end

    return 0,0
end

function Flee()
    local ga = {}
    ga = {GetGameObjects()}

    for index, value in pairs(ga)
    do
        if (value ~= n_locGameObjectID)
        then
            local x1
            local y1

            x1,y1 = GetGameObjectPosition(value)

            local x2
            local y2

            x2, y2 = GetGameObjectPosition(n_locGameObjectID)

            return x2 - x1, y2 - y1
        end
    end

    return 0,0
end

function FleeState()
    if n_locHealth > 33 then
        n_locState = 2
    end

    return Flee()
end

function ChaseState()
    if (n_locHealth < 66) then
        Print("Changing to keep distance ")
        n_locState = 2
    end

    Print("Chase ", n_locHealth, " ")

    return Chase()
end

function KeepDistanceState()
    if (n_locHealth > 66) then
        Print("Changing to Chase ")
        n_locState = 0
    elseif (n_locHealth < 33) then
        n_locState = 1
    end

    Print("Keep distance")

    local ga = {}
    ga = {GetGameObjects()}

    for index, value in pairs(ga)
    do
        if (value ~= n_locGameObjectID)
        then
            local x1
            local y1

            x1,y1 = GetGameObjectPosition(value)

            local x2
            local y2

            x2, y2 = GetGameObjectPosition(n_locGameObjectID)

            local xDist = (x1 - x2)
            local yDist = (y1 - y2)

            local dist = xDist * xDist + yDist * yDist

            if dist < 0.3 * 0.3 then
                return Flee()
            elseif dist > 0.4 * 0.4 then
                return Chase()
            else
                return 0.00001,0.000001
            end
        end
    end

    return 0,0
end

function GetDirection()
    n_locHealth = GetObjectHealth(n_locGameObjectID)
    n_locHealth = 50

    if (n_locState == 0) then
        return ChaseState()
    elseif (n_locState == 1) then
        return FleeState()
    else
        return KeepDistanceState()
    end
end
