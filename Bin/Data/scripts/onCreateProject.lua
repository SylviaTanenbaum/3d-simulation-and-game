-- onCreateProject.lua
-- called after project res was created.

-- 发布		-------------------------------------------------------------
PX2_PROJ:SetPublish(false)

-- 初始化   -------------------------------------------------------------
PX2_RM:SetUseGarbageCollect(true)
gSM = ScriptManager:GetSingleton()

-- 声音 	-------------------------------------------------------------
PX2_SS:SetMaxNumPlaySameTime(4)
PX2_SS:SetPlaySameTimeRange(0.2)

-- 调试0	-------------------------------------------------------------
PX2_PROJ:SetShowProjectInfo(true)

-- 游戏		-------------------------------------------------------------

function OnBut ()
	local scene = PX2_PROJ:GetScene()
	local actor = scene:GetActor("Man")
	actor:RegistToScriptSystem()
	
	local butName = this:GetName()
	
	if arg1 == UICT_PRESSED then		
	elseif arg1 == UICT_RELEASED then		
		actor:PlayAnimByName(butName)
	elseif arg1 == UICT_RELEASED_NOTVALIED then		
	end
end