--��ʱû��һ���ȽϺõķ�������ֹ��Class��table����һ��ʵ����ʹ��
--�������һ��Class��ʱ��һ��Ҫ���������ʵ����������
clsObject = {
		--���������Ƿ���һ������ or Class or ��ͨtable
		__ClassType = "<base class>",
		Inherit = InheritWithCopy,
	}
		

function clsObject:AttachToClass(Obj)
	setmetatable(Obj, {__ObjectType="<base object", __index = self})
	return Obj
end


function clsObject:New(...)
	local o = {}

	--û�г�ʼ����������ԣ���������Ӧ����init��������ʾ��ʼ��
	--��������࣬Ӧ�����Լ���init�������ȵ��ø����init����

	self:AttachToClass(o)

	if o.__init__ then
		o:__init__(...)
	end
	return o
end

function clsObject:__init__()
	self._destroy = false
	self._son_list = {}
	--nothing
end

function clsObject:IsClass()
	return true
end

function clsObject:GetDest()
	return self.__DestroyTime
end

function clsObject:Destroy()
	self._destroy = true
	for _, son_node in pairs(self._son_list) do
		son_node:Destroy()
	end
end

function clsObject:isDestroy()
	return self._destroy
end	

function clsObject:hide()
	self:setVisible(false)
end

function clsObject:isVisible()
	--return self._root:isVisible()
	return self:getCOObj():isVisible()
end

function clsObject:toggle()
	self:setVisible( not self:isVisible() )
end

--[[
��Щ�ؼ����ڲ�����̶���ʽ��Anchor��ʹ�ñ���������λ�û���
������
x/y����realAnchor����Ҫ���õ�λ��ֵ
fixAnchor���ؼ��ڲ��̶���Anchor��{x,y}
realAnchor���û��о��ϵ�Anchor
���ذ�fixAnchor������λ��x,y
]]
function clsObject:getPositionWithFixAnchor( x, y, fixAnchor, realAnchor )
	local size = self:getContentSize()
	
	if realAnchor.x then
		x = x + ( fixAnchor.x - realAnchor.x ) * size.width
	end
	
	if realAnchor.y then
		y = y + ( fixAnchor.y - realAnchor.y ) * size.height
	end

	return x, y
end

function clsObject:setPositionWithFixAnchor( x, y, fixAnchor, realAnchor )
	local new_x, new_y = self:getPositionWithFixAnchor( x, y, fixAnchor, realAnchor )
	self._root:setPosition(cc.p(new_x,new_y))
end

function clsObject:show()
	self:setVisible(true)
end

function clsObject:getCOObj()
	return self._root
end

function clsObject:setContentSize( width, height )
end

function clsObject:setAnchorPoint( x, y )
end

--ͳһ��װ
function clsObject:getAnchorPoint()
	return self._root and self._root:getAnchorPoint() or { x = .5, y = .5, }
end

function clsObject:getContentSize()
end

function clsObject:getPosition()
	if self._root then
		return self._root:getPosition()
	else
		return 0,0
	end
end

function clsObject:getXY()
	local a = self:getAnchorPoint()
	local s = self:getContentSize()
	local x, y = self:getPosition()
	
	return { ax = a.x, ay = a.y, sx = s.width, sy = s.height, x = x, y = y }
end

function clsObject:getX0()
	local p = self:getXY()
	return p.x - p.ax * p.sx
end

function clsObject:getX1()
	local p = self:getXY()
	return p.x + ( 1 - p.ax ) * p.sx
end

function clsObject:getX()
	local p = self:getXY()
	return p.x + ( .5 - p.ax ) * p.sx
end

function clsObject:getY0()
	local p = self:getXY()
	return p.y - p.ay * p.sy
end

function clsObject:getY1()
	local p = self:getXY()
	return p.y + ( 1 - p.ay ) * p.sy
end

function clsObject:getY()
	local p = self:getXY()
	return p.y + ( .5 - p.ay ) * p.sy
end

function clsObject:getSx()
	local size = self:getContentSize()
	return size.width
end

function clsObject:getSy()
	local size = self:getContentSize()
	return size.height
end

function clsObject:makeObjMouseEventHandle(obj, stopMessage )
	local function onTouch(eventType, x, y)
		if eventType == "began" then
			return obj:onTouchBegan(x, y)
		elseif eventType == "ended" then
			return obj:onTouchEnd(x, y)
		else
			return obj:onTouchMove(x, y)			
		end
	end
	
	if not stopMessage and stopMessage ~= false then
		stopMessage = true
	end
	obj:registerScriptTouchHandler(onTouch, false, 0, stopMessage)
	obj:setTouchEnabled(true)
end	

function getClass()
	return clsObject
end	