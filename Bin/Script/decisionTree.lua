local n_locSpeed
local n_locScriptID
local n_locGameObjectID
local n_locHealth

function Init(n_aScriptID, n_aGameObjectID)
    n_locScriptID = n_aScriptID
    n_locGameObjectID = n_aGameObjectID

    n_locHealth = GetObjectHealth(n_locGameObjectID)
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

function GetDirection()
    n_locHealth = GetObjectHealth(n_locGameObjectID)

    local x = 0
    local y = 0

    if (n_locHealth >= 66)
    then
        x, y = Chase()
    elseif (n_locHealth <= 33)
    then
        x, y = Flee()
    else
        x = 0
        y = 0
    end

    return x,y
end
