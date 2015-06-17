local const = trans.const
local err = trans.err
local base = trans.base

const.kPathUserLoad		= 1764226070		-- 玩家数据加载成功
const.kPathUserInit		= 26069095		-- 玩家初始化
const.kPathUserLogin		= 367449528		-- 用户登录
const.kPathUserEveryDay		= 1821417889		-- 玩家每天处理
const.kPathUserMeet		= 777059757		-- 用户数据访问

err.kErrUser		= 242729488
err.kErrUserNoExist		= 1796763675		--玩家不存在

-- 用户简易信息结构
base.reg( 'SUserSimple', nil,
    {
        { 'platform', 'string' },
        { 'name', 'string' },
        { 'gender', 'uint8' },		-- 性别
        { 'avatar', 'uint16' },		-- 头像信息
        { 'team_level', 'uint32' },		-- 战队等级
        { 'team_xp', 'uint32' },		-- 战队经验
        { 'vip_level', 'uint32' },		-- vip等级
        { 'vip_xp', 'uint32' },		-- vip经验
        { 'fight_value', 'uint32' },		-- 战斗力
        { 'strength', 'uint32' },		-- 体力点
        { 'guild_id', 'uint32' },		-- 公会Id
    }
)

-- 用户基本信息结构
base.reg( 'SUserInfo', nil,
    {
        { 'online_time_all', 'uint32' },		-- 上线总时间(秒)
        { 'history_fight_value', 'uint32' },		-- 历史最大战斗力
    }
)

-- 用户保护性数据结构( 保存至服务器, 但绝不会发送给本用户以外的其它用户 )
base.reg( 'SUserProtect', nil,
    {
        { 'session', 'uint32' },
        { 'lock_time', 'uint32' },		-- 用于临时锁定用户可能产生冲突的操作, 例如: 创建公会, 角色改名等
    }
)

-- 用户浏览面板信息结构
base.reg( 'SUserPanel', nil,
    {
        { 'simple', 'SUserSimple' },
        { 'info', 'SUserInfo' },
    }
)

base.reg( 'SUserSingleArenaPanel', 'SUserPanel',
    {
        { 'formation_map', { 'array', 'SUserFormation' } },		-- 玩家阵型
        { 'soldier_map', { 'indices', 'SUserSoldier' } },		-- 武将列表
        { 'totem_info', 'STotemInfo' },		-- 图腾信息
    }
)

-- 玩家墓地信息
base.reg( 'SUserTombPanel', 'SUserPanel',
    {
        { 'formation_map', { 'array', 'SUserFormation' } },		-- 玩家阵型
        { 'soldier_map', { 'indices', 'SUserSoldier' } },		-- 武将列表
        { 'totem_info', 'STotemInfo' },		-- 图腾信息
        { 'fightextable_map', { 'array', 'SFightExtAbleInfo' } },		-- 战斗属性
    }
)

-- 用户存储数据库的所有数据结构
base.reg( 'SUserData', nil,
    {
        { 'simple', 'SUserSimple' },
        { 'other', 'SUserOther' },
        { 'team', 'STeamInfo' },		-- 战队信息
        { 'info', 'SUserInfo' },
        { 'protect', 'SUserProtect' },
        { 'coin', 'SUserCoin' },		-- 货币信息
        { 'copy', 'SUserCopy' },		-- 当前副本信息
        { 'star', 'SUserStar' },		-- 星星总数
        { 'gut', 'SGutInfo' },		-- 当前剧情信息
        { 'mopup', 'SCopyMopup' },		-- 扫荡信息
        { 'friend_map', { 'indices', 'SUserFriend' } },		-- 好友列表
        { 'friend_limit_map', { 'indices', 'SFriendLimit' } },		-- 好友赠送限制
        { 'mail_map', { 'indices', 'SUserMail' } },		-- 邮件列表
        { 'item_map', { 'indices', 'array', 'SUserItem' } },		-- 物品列表
        { 'formation_map', { 'indices', 'array', 'SUserFormation' } },		-- 玩家阵型
        { 'fightextable_map', { 'indices', 'array', 'SFightExtAbleInfo' } },		-- 战斗属性
        { 'soldier_map', { 'indices', 'indices', 'SUserSoldier' } },		-- 武将列表
        { 'building_list', { 'array', 'SUserBuilding' } },		-- 建筑群
        { 'copy_log_map', { 'indices', 'SCopyLog' } },		-- 副本通关列表
        { 'area_log_map', { 'indices', 'SAreaLog' } },		-- 副本区域通关列表
        { 'shop_log', { 'array', 'SUserShopLog' } },		-- 商店购买记录
        { 'totem_map', { 'indices', 'STotemInfo' } },		-- 图腾信息列表
        { 'task_map', { 'indices', 'SUserTask' } },		-- 任务列表
        { 'task_log_map', { 'indices', 'SUserTaskLog' } },		-- 任务记录列表
        { 'task_day_map', { 'indices', 'SUserTaskDay' } },		-- 日常任务列表
        { 'sign_info', 'SSignInfo' },		-- 签到信息
        { 'altar_info', 'SAltarInfo' },		-- 祭坛信息
        { 'pay_list', { 'array', 'SUserPay' } },		-- 充值List
        { 'pay_info', 'SUserPayInfo' },		-- 充值信息
        { 'copy_material_list', { 'array', 'SUserCopyMaterial' } },		-- 副本原料
        { 'mystery_goods_list', { 'array', 'SUserMysteryGoods' } },		-- 神秘商店商品列表
        { 'var_map', { 'map', 'SUserVar' } },		-- key-value
        { 'trial_map', { 'indices', 'SUserTrial' } },		-- 试炼
        { 'trial_reward_map', { 'indices', 'array', 'SUserTrialReward' } },		-- 试炼奖励
        { 'tomb_info', 'SUserTomb' },		-- 墓地信息
        { 'tomb_target_list', { 'array', 'STombTarget' } },		-- 对战信息
        { 'market_log', { 'array', 'SMarketLog' } },		-- 拍卖行交易记录
        { 'equip_suit_level', { 'array', 'uint32' } },		-- 装备套装生效等级
        { 'temple', 'STempleInfo' },		-- 神殿
        { 'viptimelimit_goods_list', { 'array', 'SUserVipTimeLimitGoods' } },		-- vip限时商店商品列表
        { 'equip_grade_list', { 'array', 'SUserEquipGrade' } },		-- 装备系别评分
        { 'bias_map', { 'indices', 'SUserBias' } },		-- 偏向性掉落数据
        { 'day_task_reward_list', { 'array', 'uint32' } },		-- 日常任务积分已领奖励列表
    }
)

-- 用户存储数据库的零散数据，最好是基本类型数据
base.reg( 'SUserOther', nil,
    {
        { 'single_arena_rank', 'uint32' },		-- 玩家竞技场最高排名
        { 'single_arena_win_times', 'uint32' },		-- 玩家竞技场战胜次数 注：离线不算
        { 'paper_skill', 'uint32' },		-- 玩家手工技能
        { 'mystery_refresh_time', 'uint32' },		-- 神秘商店下次刷新时间戳
        { 'purview', 'uint32' },		-- 权限[ kBackXXX ]
        { 'chat_ban_endtime', 'uint32' },		-- 玩家禁言结束时间
        { 'last_action', 'string' },		-- 最后行为记录
        { 'market_day_get', 'uint32' },		-- 拍卖行当天收入
        { 'market_day_cost', 'uint32' },		-- 拍卖行当天消耗
        { 'market_day_time', 'uint32' },		-- 拍卖行时间戳
        { 'market_cost_time', 'uint32' },		-- 拍卖行花费时间戳 market_day_time为获取
    }
)

-- 用户扩展信息结构( 不保存至数据库,只用于服务器内部临时保存 )
base.reg( 'SUserExt', nil,
    {
        { 'role_id', 'uint32' },		-- 玩家id
        { 'session', 'uint32' },		-- session
        { 'fight_id', 'uint32' },		-- 战斗ID
        { 'check', { 'map', 'S4Int32' } },		-- 用户数据一致性校验
        { 'operate_time', 'uint32' },		-- 最后操作时间( 以客户端发 PQSystemOnline 为准 )
        { 'meet_time', 'uint32' },		-- 最后访问时间
        { 'save_time', 'uint32' },		-- 最后保存时间
        { 'trial_id', 'uint32' },		-- 试炼ID
        { 'trial_time', 'uint32' },		-- 进入试炼的时间
        { 'apply_guilds', { 'array', 'uint32' } },		-- 已申请的公会
    }
)

-- 用户数据集合
base.reg( 'SUser', nil,
    {
        { 'guid', 'uint32' },
        { 'data', 'SUserData' },
        { 'ext', 'SUserExt' },
    }
)

-- ============================数据中心========================
base.reg( 'CUserMap', nil,
    {
        { 'user_map', { 'indices', 'SUser' } },		-- 用户数据集合
        { 'save_index', 'int32' },		-- 数据保存索引
        { 'user_name_id', { 'map', 'uint32' } },		-- 名称映射id
        { 'user_id_name', { 'indices', 'string' } },		-- id映射名称
    }
)

-- =========================通迅协议============================
base.reg( 'PQUserSimple', 'SMsgHead',
    {
        { 'target_id', 'uint32' },
    }, 455141318
)

base.reg( 'PRUserSimple', 'SMsgHead',
    {
        { 'target_id', 'uint32' },
        { 'data', 'SUserSimple' },
    }, 1175044508
)

base.reg( 'PQUserData', 'SMsgHead',
    {
    }, 955700884
)

base.reg( 'PRUserData', 'SMsgHead',
    {
        { 'data', 'SCompressData' },		-- SUserData
    }, 2136523129
)

base.reg( 'PRUserOther', 'SMsgHead',
    {
        { 'other', 'SUserOther' },
    }, 2131699547
)

base.reg( 'PQUserPanel', 'SMsgHead',
    {
        { 'target_id', 'uint32' },
    }, 945575969
)

base.reg( 'PRUserPanel', 'SMsgHead',
    {
        { 'target_id', 'uint32' },
        { 'data', 'SUserPanel' },
    }, 1395064671
)

base.reg( 'PQUserSingleArenaPanel', 'SMsgHead',
    {
        { 'target_id', 'uint32' },
    }, 78072471
)

base.reg( 'PRUserSingleArenaPanel', 'SMsgHead',
    {
        { 'target_id', 'uint32' },
        { 'data', 'SUserSingleArenaPanel' },
    }, 1447792173
)

base.reg( 'PQUserTombPanel', 'SMsgHead',
    {
        { 'target_id', 'uint32' },
    }, 923525520
)

base.reg( 'PRUserTombPanel', 'SMsgHead',
    {
        { 'target_id', 'uint32' },
        { 'data', 'SUserTombPanel' },
    }, 2067373703
)

-- 用户行为记录
base.reg( 'PQUserActionSave', 'SMsgHead',
    {
        { 'last_action', 'string' },
    }, 658374206
)

-- 每天定时处理(6:00)
base.reg( 'PRUserTimeLimit', 'SMsgHead',
    {
    }, 1931081387
)


