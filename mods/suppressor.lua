local valueMods = {

    { "damage", 1.5 },
    { "bulletSpeed", 1.0 },
    { "shotDelay", -0.5 },
    { "magSize", 500, "+" },
    { "reloadSpeedMultiplier", -0.9 },

    { "spread", -1.0 },
    { "shotDeviation", -1.0 },
    { "spreadDecrease", 5.0 },
    { "cameraZoomMultAim", 1.0 },
    { "clumpSpread", -1.0 },
    { "spreadPerShot", -1.0 },
    { "spreadPerShotMultiplier", -1.0 },
    { "lookSpreadMax", -1.0 },
    { "lookSpreadAngleMultiplier", -1.0 },
    { "maxSpreadIncrease", -1.0 },
    { "spreadVelocityIncrease", 5.0 },
    { "focusSpreadSpeed", 5.0 },
    { "focusSpread", 1.0 },

    { "noiseRadius", -1.0 },
    { "noiseChange", -1.0, "+" },
    { "slowdown", -0.3, "+" },

}

local modNames = {
    "suppressor_nonpistol",
    "suppressor_pistol",
    "suppressor_pistol_lp",
    "suppressor_pistol_manual"
}

for k, v in pairs(modNames) do
    local data = weapons.getModData(v)
    data.valueMods = valueMods
    data:onRegister()
end
