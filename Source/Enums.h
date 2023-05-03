#pragma once
enum class eAckCode : std::uint32_t
{
	ACKCODE_SUCCESS,
	ACKCODE_FAIL,
	ACKCODE_WRONG_OWNER,
	ACKCODE_OUT_OF_SEQUENCE,
	ACKCODE_NO_OBJECT,
	ACKCODE_TOO_MANY_OBJECTS,
	ACKCODE_CANT_APPLY_DATA,
	ACKCODE_MATCH_NOT_STARTED,
	ACKCODE_NONE
};
enum class eNetObjType
{
	NET_OBJ_TYPE_AUTOMOBILE,
	NET_OBJ_TYPE_BIKE,
	NET_OBJ_TYPE_BOAT,
	NET_OBJ_TYPE_DOOR,
	NET_OBJ_TYPE_HELI,
	NET_OBJ_TYPE_OBJECT,
	NET_OBJ_TYPE_PED,
	NET_OBJ_TYPE_PICKUP,
	NET_OBJ_TYPE_PICKUP_PLACEMENT,
	NET_OBJ_TYPE_PLANE,
	NET_OBJ_TYPE_SUBMARINE,
	NET_OBJ_TYPE_PLAYER,
	NET_OBJ_TYPE_TRAILER,
	NET_OBJ_TYPE_TRAIN
};
enum class eRemoteEvent
{
	Bounty = 1459520933, // (137, "FM_TXT_BNTY0", iVar1, PLAYER::GET_PLAYER_NAME(Var2.f_1), "", 5000, Var2.f_6);
	CeoBan = 1517094008, // mpply_vipgameplaydisabledtimer
	CeoKick = 1421455565,
	CeoMoney = 75579707, // Goon_Paid_Large
	ClearWantedLevel = 1743540940,
	ForceMission = -2138393348, // ), Var0.f_2, 1))
	GiveCollectible = 1839167950,  // DLC_SUM20_HIDDEN_COLLECTIBLES xref
	GtaBanner = 2114252738,  // NETWORK::NETWORK_IS_SCRIPT_ACTIVE("BUSINESS_BATTLES", -1, true, 0) second one
	NetworkBail = 1017995959,  // NETWORK::NETWORK_BAIL(16, 0, 0); xref func
	PersonalVehicleDestroyed = -642631978,  // PLYVEH_INS_DES1
	RemoteOffradar = 1141648445,  // NETWORK::GET_TIME_DIFFERENCE(NETWORK::GET_NETWORK_TIME(), Var0.f_2)
	SendToCutscene = 2139870214,  // (bVar3, bVar4, 125f, 1)
	SendToCayoPerico = -369672308,  // CELL_HI_INV
	SendToLocation = 330622597,   // &Var222, 11);
	SoundSpam = 36077543,    // CELL_APTINVYACHT
	Spectate = -2029707091, // SPEC_TCK1
	Teleport = -702866045,  // Mission_Pass_Notify
	TeleportToWarehouse = -1796714618, // .f_4 == 50
	TransactionError = 54323524,    // NETWORK_RECEIVE_PLAYER_JOBSHARE_CASH
	VehicleKick = -1603050746, // PIM_RFMOC
	MCTeleport = 891653640,  // NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(PLAYER::PLAYER_ID()) == (first one)
	StartActivity = 1104117595, // (Var0.f_2, -1); first match
	MarkPlayerAsBeast = -1721728321, // GB_BOSSBST xref == PLAYER... global (sadly doesn't actually turn people into the beast)
	KickFromInterior = 786522321, // ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), PED::GET_PED_MAX_HEALTH(PLAYER::PLAYER_PED_ID()), false)
	InteriorControl = 1727896103, // eventData.f_3 != _INVALID_PLAYER_INDEX_0()
	SMS = 53975141,
	SendTextLabelSMS = 1075676399,

	Crash1 = -992162568, // SET_NO_LOADING_SCREEN, xref it
	Crash2 = 1131623211,
	Crash3 = 1556360603,

	TSECommand = -1428749433,                                       // CnCTG_IN_BF
	TSECommandRotateCam = 448051697 /*joaat("pats_horse_right") in script*/, // != 29) && f

	Notification = 2041805809,
	NotificationMoneyBanked = 276906331, // TICK_TC_BANK
	NotificationMoneyRemoved = 853249803, // TICK_TC_REMO
	NotificationMoneyStolen = 82080686,  // TICK_TC_STOL

	DestroyPersonalVehicle = -2101545224, // CnC_PV_THEFT
	TriggerCEORaid = -1388385133,

	StartScriptBegin = -95341040,
	StartScriptProceed = 1742713914
};

enum eVehicleFlags
{
	TRIGGER_SPAWN_TOGGLE = 1 << 0,
	DESTROYED = 1 << 1,
	HAS_INSURANCE = 1 << 2,
	UNK0 = 1 << 3,
	IMPOUNDED = 1 << 6,
	UNK1 = 1 << 10,
	SPAWN_AT_MORS_MUTUAL = 1 << 11,
	UNK2 = 1 << 16
};
enum eBusySpinnerType
{
	BUSY_SPINNER_LEFT,
	BUSY_SPINNER_LEFT_2,
	BUSY_SPINNER_LEFT_3,
	BUSY_SPINNER_SAVE,
	BUSY_SPINNER_RIGHT,
};
enum class eNetworkEvents : uint16_t
{
	CObjectIdFreedEvent,
	CObjectIdRequestEvent,
	CArrayDataVerifyEvent,
	CScriptArrayDataVerifyEvent,
	CRequestControlEvent,
	CGiveControlEvent,
	CWeaponDamageEvent,
	CRequestPickupEvent,
	CRequestMapPickupEvent,
	CGameClockEvent,
	CGameWeatherEvent,
	CRespawnPlayerPedEvent,
	CGiveWeaponEvent,
	CRemoveWeaponEvent,
	CRemoveAllWeaponsEvent,
	CVehicleComponentControlEvent,
	CFireEvent,
	CExplosionEvent,
	CStartProjectileEvent,
	CUpdateProjectileTargetEvent,
	CRemoveProjectileEntityEvent,
	CBreakProjectileTargetLockEvent,
	CAlterWantedLevelEvent,
	CChangeRadioStationEvent,
	CRagdollRequestEvent,
	CPlayerTauntEvent,
	CPlayerCardStatEvent,
	CDoorBreakEvent,
	CScriptedGameEvent,
	CRemoteScriptInfoEvent,
	CRemoteScriptLeaveEvent,
	CMarkAsNoLongerNeededEvent,
	CConvertToScriptEntityEvent,
	CScriptWorldStateEvent,
	CClearAreaEvent,
	CClearRectangleAreaEvent,
	CNetworkRequestSyncedSceneEvent,
	CNetworkStartSyncedSceneEvent,
	CNetworkStopSyncedSceneEvent,
	CNetworkUpdateSyncedSceneEvent,
	CIncidentEntityEvent,
	CGivePedScriptedTaskEvent,
	CGivePedSequenceTaskEvent,
	CNetworkClearPedTasksEvent,
	CNetworkStartPedArrestEvent,
	CNetworkStartPedUncuffEvent,
	CNetworkSoundCarHornEvent,
	CNetworkEntityAreaStatusEvent,
	CNetworkGarageOccupiedStatusEvent,
	CPedConversationLineEvent,
	CScriptEntityStateChangeEvent,
	CNetworkPlaySoundEvent,
	CNetworkStopSoundEvent,
	CNetworkPlayAirdefenseFireEvent,
	CNetworkBankRequestEvent,
	CNetworkAudioBarkEvent,
	CRequestDoorEvent,
	CNetworkTrainReportEvent,
	CNetworkTrainRequestEvent,
	CNetworkIncrementStatEvent2,
	CModifyVehicleLockWordStateData,
	CModifyPtfxWordStateDataScriptedEvolveEvent,
	CRequestPhoneExplosionEvent,
	CRequestDetachmentEvent,
	CKickVotesEvent,
	CGivePickupRewardsEvent,
	CNetworkCrcHashCheckEvent,
	CBlowUpVehicleEvent,
	CNetworkSpecialFireEquippedWeapon,
	CNetworkRespondedToThreatEvent,
	CNetworkShoutTargetPosition,
	CVoiceDrivenMouthMovementFinishedEvent,
	CPickupDestroyedEvent,
	CUpdatePlayerScarsEvent,
	CNetworkCheckExeSizeEvent,
	CNetworkPtfxEvent,
	CNetworkPedSeenDeadPedEvent,
	CRemoveStickyBombEvent,
	CNetworkCheckCodeCrcsEvent,
	CInformSilencedGunshotEvent,
	CPedPlayPainEvent,
	CCachePlayerHeadBlendDataEvent,
	CRemovePedFromPedgroupEvent,
	CUpdateFxnEvent,
	CReportCashSpawnEvent,
	CActivateVehicleSpecialAbilityEvent,
	CBlockWeaponSelection,
	CNetworkCheckCatalogCrc
};
enum class option_data {
	delay = 50
};
enum class BlipColors
{
	None,
	Red,
	Green,
	Blue,
	PlayerColor,
	YellowMission,
	FriendlyVehicle = 0x26,
	MichaelColor = 0x2A,
	FranklinColor,
	TravorColor,
	BlipColorEnemy = 0x31,
	MissionVehicle = 0x36,
	RedMission = 0x3B,
	YellowMission2 = 0x3C,
	Mission = 0x42,
	WaypointColor = 0x54
};

enum class BlipIcons
{
	Null,
	Circle,
	Empty,
	Cop,
	CopSearchZone,
	Square,
	PlayerArrow,
	North,
	Waypoint,
	BigCircle,
	BigCircleOutline,
	ArrowUpOutlined,
	ArrowDownOutlined,
	ArrowUp,
	ArrowDown,
	PoliceHelicopter,
	Jet,
	Number1,
	Number2,
	Number3,
	Number4,
	Number5,
	Number6,
	Number7,
	Number8,
	Number9,
	Number10,
	GTAOCrew,
	GTAOFriend,
	CableCar = 36,
	RaceFinish = 38,
	Safehouse = 40,
	Cop2,
	CopCar,
	Helicopter,
	ChatBubble = 47,
	Garage = 50,
	Drugs,
	ConvenienceStore,
	PoliceCar = 56,
	Circle2,
	CircleWithStar,
	ConvenienceStore2,
	ShieldWithStar,
	Asterisk,
	Helicopter2 = 64,
	StrangersAndFreaks = 66,
	ArmoredTruck,
	TowTruck,
	Barber = 71,
	LosSantosCustoms,
	Clothes,
	TattooParlor = 75,
	Simeon,
	Lester,
	Michael,
	Trevor,
	Heist1,
	Rampage = 84,
	VinewoodTours,
	Franklin,
	Franklin2 = 88,
	Chinese,
	FlightSchool,
	Bar = 93,
	ParachuteJump,
	Heist2 = 96,
	CarWash = 100,
	ComedyClub = 102,
	Darts,
	FIB = 106,
	Heist3,
	DollarSign,
	Golf,
	AmmuNation,
	Exile = 112,
	ShootingRange = 119,
	Solomon,
	StripClub,
	Tennis,
	Triathlon = 126,
	OffRoadRaceFinish,
	Key = 134,
	MovieTheater,
	Music,
	Marijuana = 140,
	Hunting,
	ArmsTraffickingGround = 147,
	Nigel = 149,
	AssaultRifle,
	Bat,
	Grenade,
	Health,
	Knife,
	Molotov,
	Pistol,
	RPG,
	Shotgun,
	SMG,
	Sniper,
	SonicWave,
	PointOfInterest,
	GTAOPassive,
	GTAOUsingMenu,
	Link = 171,
	Minigun = 173,
	GrenadeLauncher,
	Armor,
	Castle,
	CameraIcon = 184,
	Handcuffs = 188,
	Yoga = 197,
	Cab,
	Number11,
	Number12,
	Number13,
	Number14,
	Number15,
	Number16,
	Shrink,
	Epsilon,
	PersonalVehicleCar = 225,
	PersonalVehicleBike,
	Custody = 237,
	ArmsTraffickingAir = 251,
	Fairground = 266,
	PropertyManagement,
	Altruist = 269,
	Enemy,
	Chop = 273,
	Dead,
	Hooker = 279,
	Friend,
	BountyHit = 303,
	GTAOMission,
	GTAOSurvival,
	CrateDrop,
	PlaneDrop,
	Sub,
	Race,
	Deathmatch,
	ArmWrestling,
	AmmuNationShootingRange = 313,
	RaceAir,
	RaceCar,
	RaceSea,
	GarbageTruck = 318,
	Motorcycle = 348,
	SafehouseForSale = 350,
	Package,
	MartinMadrazo,
	EnemyHelicopter,
	Boost,
	Devin,
	Marina,
	Garage2,
	GolfFlag,
	Hangar,
	Helipad,
	JerryCan,
	Masks,
	HeistSetup,
	Incapacitated,
	PickupSpawn,
	BoilerSuit,
	Completed,
	Rockets,
	GarageForSale,
	HelipadForSale,
	MarinaForSale,
	HangarForSale,
	Business = 374,
	BusinessForSale,
	RaceBike,
	Parachute,
	TeamDeathmatch,
	RaceFoot,
	VehicleDeathmatch,
	Barry,
	Dom,
	MaryAnn,
	Cletus,
	Josh,
	Minute,
	Omega,
	Tonya,
	Paparazzo,
	Crosshair,
	Creator = 398,
	CreatorDirection,
	Abigail,
	Blimp,
	Repair,
	Testosterone,
	Dinghy,
	Fanatic,
	GangAttack,
	Information,
	CaptureBriefcase,
	LastTeamStanding,
	Boat,
	CaptureHouse,
	JerryCan2 = 415,
	RPLogo,
	GTAOPlayerSafehouse,
	GTAOPlayerSafehouseBounty,
	CaptureAmericanFlag,
	CaptureFlag,
	Tank,
	PlayerHelicopter,
	PlayerPlane,
	PlayerJet,
	PlayerArrowNoColor,
	PlayerLAPV,
	PlayerBoat,
	HeistRoom,
	Stopwatch = 430,
	DollarSignCircled,
	Crosshair2,
	Crosshair3,
	DollarSignSquared,
	RaceFlagWithArrow,
	Fire,
	DoubleDeathmatchSkulls,
	CastleIcon,
	Crown,
	SupplyBag,
	QuadirectionalArrows,
	Fox,
	Triangle,
	ThreeBars,
	LamarDavis,
	Mechanic,
	LamarDavisOne,
	LamarDavisTwo,
	LamarDavisThree,
	LamarDavisFour,
	LamarDavisFive,
	LamarDavisSix,
	LamarDavisSeven,
	LamarDavisEight,
	Yacht,
	SmallQuestionMark,
	GymBag,
	CrosshairWithPersonInMiddle,
	PlayerSpeaking,
	Taxi,
	ShieldWithX,
	YachtMinimap,
	Fox2,
	Hourglass,
	SmallQuestionMark2,
	Stopwatch2,
	Restart,
	SunWithEye,
	Marijuana2,
	Shotgun2,
	Jetski,
	EyeWithLineThroughIt,
	Garage3,
	GarageForSale2,
	Building,
	BuildingForSale,
	Truck,
	Crate,
	Trailer,
	Person,
	Cargobob,
	BigOutlineSquare,
	Speedometer,
	Ghost,
	RemoteControl,
	Bomb,
	Shield,
	StuntRace,
	Heart,
	StuntRaceMoney,
	TeamDeathMatch2,
	HouseWithGarage,
	QuadirectionalArrowsWithMotorcycle,
	CircleWithMotorcycle,
	MotorcycleRace,
	Weed,
	Cocaine,
	ForgedDocuments,
	Meth,
	CounterfeitMoney,
	DrugPickup,
	BigOne,
	BigTwo,
	BigThree,
	BigFour,
	BigFive,
	BigSix,
	BigSeven,
	BigEight,
	BigNine,
	BigTen,
	ATVQuad,
	Bus,
	BagMaybe,
	UpArrowOnSquare,
	FourPlayers,
	EightPlayers,
	TenPlayers,
	TwelvePlayers,
	SixteenPlayers,
	Laptop,
	Supercycle,
	Supercar,
	GarageWithCar,
	PaperDocument,
	ShieldWithBlackStar,
	CraneClaw,
	PhantomWedge,
	BoxvilleArmored,
	Ruiner2000,
	RampBuggy,
	Wastelander,
	RocketVoltic,
	TechnicalAqua,
	LetterA,
	LetterB,
	LetterC,
	LetterD,
	LetterE,
	LetterF,
	LetterG,
	LetterH,
	SkullWithTriangleTop,
	Wrench,
	SteeringWheel,
	Trolphy,
	Rocket,
	Missile,
	Bullets,
	Parachute2,
	Number5WithCircle,
	Number10WithCircle,
	Number15WithCircle,
	Number20WithCircle,
	Number30WithCircle,
	Bullets2,
	Bunker,
	InsurgentPickup,
	Opressor,
	TechnicalCustom,
	DuneFAV,
	HalfTrack,
	AntiAircraftTrailer,
	Satelite,
	BunkerWithPeople,
	ScrewdriverAndHammer,
	UpgradedWeaponWorkbench,
	CrateWithStraps,
	AircraftHanger,
	Icosikaitetragon,
	RaceflagWithQuestionmark,
	AlphaZ1,
	Bombushka,
	Havok,
	HowardNX25,
	Hunter,
	Ultralight,
	Mogul,
	Molotok,
	Nokota,
	Pyro,
	Rogue,
	Starling,
	Starbreeze,
	Tula,
	GymBagWithLetterH,
	LockedCrate,
	SateliteIcon,
	Avenger,
	IAAFacility,
	DoomsdayHeist,
	SAMTurret,
	HackingPuzzleRed,
	HackingPuzzleDiode,
	Stromburg,
	Deluxo,
	ThrusterJetpack,
	TM02KhanjaliTank,
	RCV,
	Volatol,
	Barrage,
	Akula,
	Chernobog,
	SpeakerMaybe,
	YellowishBrownMoneySign,
	ComputerTerminal,
	HackingPuzzleMirror,
	HackingPuzzleReflector,
	HackingPuzzleRotator,
	RaceFlagWithCrosshair,
	RaceFlagWithSteeringWheel,
	SeaSparrow,
	Caracara,
	Nightclub,
	CrateB,
	VanB,
	Diamond,
	BullionStacks,
	CalculatorMaybe,
	CarWithLightningBolt,
	HeartIcon,
	StarWithAdd,
	StarWithSubtract,
	BombWithAdd,
	BombWithSubtract,
	CrosshairDJ,
	Drone,
	Cashregister,
	SpeakerMaybeBigger,
	Skull,
	FestivalBus,
	Terrorbyte,
	Menacer,
	Scramjet,
	PounderCustom,
	MuleCustom,
	SpeedoCustom,
	BlimpIcon,
	OpressorMKII,
	B11StrikeForce,
	GearWithCar,
	GearWithMoney,
	GearWithWrench,
	RaceFlagWithGear,
	CrosshairOnCar,
	RCBandito,
	RCRemote,
	FlameSign,
	ArrowSign,
	GearSign,
	RepeatSign,
	DownArrowSign,
	ExplosionSign,
	WheelExplosionSign,
	ElevatorSign,
	ElevatorSign2,
	EjectorPlatformSign,
	Bruiser,
	Brutus,
	Cerberus,
	Deathbike,
	Dominator,
	Impaler,
	Imperator,
	Issi,
	Sasquatch,
	Scarab,
	Slamvan,
	ZR380
};
enum class eSessionType
{
	JOIN_PUBLIC,
	NEW_PUBLIC,
	CLOSED_CREW,
	CREW,
	CLOSED_FRIENDS = 6,
	FIND_FRIEND = 9,
	SOLO,
	INVITE_ONLY,
	JOIN_CREW,
	SC_TV,
	LEAVE_ONLINE = -1
};
enum PedBones : std::uint32_t
{
	SKEL_ROOT = 0x0,
	SKEL_Pelvis = 0x2E28,
	SKEL_L_Thigh = 0xE39F,
	SKEL_L_Calf = 0xF9BB,
	SKEL_L_Foot = 0x3779,
	SKEL_L_Toe0 = 0x83C,
	EO_L_Foot = 0x84C5,
	EO_L_Toe = 0x68BD,
	IK_L_Foot = 0xFEDD,
	PH_L_Foot = 0xE175,
	MH_L_Knee = 0xB3FE,
	SKEL_R_Thigh = 0xCA72,
	SKEL_R_Calf = 0x9000,
	SKEL_R_Foot = 0xCC4D,
	SKEL_R_Toe0 = 0x512D,
	EO_R_Foot = 0x1096,
	EO_R_Toe = 0x7163,
	IK_R_Foot = 0x8AAE,
	PH_R_Foot = 0x60E6,
	MH_R_Knee = 0x3FCF,
	RB_L_ThighRoll = 0x5C57,
	RB_R_ThighRoll = 0x192A,
	SKEL_Spine_Root = 0xE0FD,
	SKEL_Spine0 = 0x5C01,
	SKEL_Spine1 = 0x60F0,
	SKEL_Spine2 = 0x60F1,
	SKEL_Spine3 = 0x60F2,
	SKEL_L_Clavicle = 0xFCD9,
	SKEL_L_UpperArm = 0xB1C5,
	SKEL_L_Forearm = 0xEEEB,
	SKEL_L_Hand = 0x49D9,
	SKEL_L_Finger00 = 0x67F2,
	SKEL_L_Finger01 = 0xFF9,
	SKEL_L_Finger02 = 0xFFA,
	SKEL_L_Finger10 = 0x67F3,
	SKEL_L_Finger11 = 0x1049,
	SKEL_L_Finger12 = 0x104A,
	SKEL_L_Finger20 = 0x67F4,
	SKEL_L_Finger21 = 0x1059,
	SKEL_L_Finger22 = 0x105A,
	SKEL_L_Finger30 = 0x67F5,
	SKEL_L_Finger31 = 0x1029,
	SKEL_L_Finger32 = 0x102A,
	SKEL_L_Finger40 = 0x67F6,
	SKEL_L_Finger41 = 0x1039,
	SKEL_L_Finger42 = 0x103A,
	PH_L_Hand = 0xEB95,
	IK_L_Hand = 0x8CBD,
	RB_L_ForeArmRoll = 0xEE4F,
	RB_L_ArmRoll = 0x1470,
	MH_L_Elbow = 0x58B7,
	SKEL_R_Clavicle = 0x29D2,
	SKEL_R_UpperArm = 0x9D4D,
	SKEL_R_Forearm = 0x6E5C,
	SKEL_R_Hand = 0xDEAD,
	SKEL_R_Finger00 = 0xE5F2,
	SKEL_R_Finger01 = 0xFA10,
	SKEL_R_Finger02 = 0xFA11,
	SKEL_R_Finger10 = 0xE5F3,
	SKEL_R_Finger11 = 0xFA60,
	SKEL_R_Finger12 = 0xFA61,
	SKEL_R_Finger20 = 0xE5F4,
	SKEL_R_Finger21 = 0xFA70,
	SKEL_R_Finger22 = 0xFA71,
	SKEL_R_Finger30 = 0xE5F5,
	SKEL_R_Finger31 = 0xFA40,
	SKEL_R_Finger32 = 0xFA41,
	SKEL_R_Finger40 = 0xE5F6,
	SKEL_R_Finger41 = 0xFA50,
	SKEL_R_Finger42 = 0xFA51,
	PH_R_Hand = 0x6F06,
	IK_R_Hand = 0x188E,
	RB_R_ForeArmRoll = 0xAB22,
	RB_R_ArmRoll = 0x90FF,
	MH_R_Elbow = 0xBB0,
	SKEL_Neck_1 = 0x9995,
	SKEL_Head = 0x796E,
	IK_Head = 0x322C,
	FACIAL_facialRoot = 0xFE2C,
	FB_L_Brow_Out_000 = 0xE3DB,
	FB_L_Lid_Upper_000 = 0xB2B6,
	FB_L_Eye_000 = 0x62AC,
	FB_L_CheekBone_000 = 0x542E,
	FB_L_Lip_Corner_000 = 0x74AC,
	FB_R_Lid_Upper_000 = 0xAA10,
	FB_R_Eye_000 = 0x6B52,
	FB_R_CheekBone_000 = 0x4B88,
	FB_R_Brow_Out_000 = 0x54C,
	FB_R_Lip_Corner_000 = 0x2BA6,
	FB_Brow_Centre_000 = 0x9149,
	FB_UpperLipRoot_000 = 0x4ED2,
	FB_UpperLip_000 = 0xF18F,
	FB_L_Lip_Top_000 = 0x4F37,
	FB_R_Lip_Top_000 = 0x4537,
	FB_Jaw_000 = 0xB4A0,
	FB_LowerLipRoot_000 = 0x4324,
	FB_LowerLip_000 = 0x508F,
	FB_L_Lip_Bot_000 = 0xB93B,
	FB_R_Lip_Bot_000 = 0xC33B,
	FB_Tongue_000 = 0xB987,
	RB_Neck_1 = 0x8B93,
	SPR_L_Breast = 0xFC8E,
	SPR_R_Breast = 0x885F,
	IK_Root = 0xDD1C,
	SKEL_Neck_2 = 0x5FD4,
	SKEL_Pelvis1 = 0xD003,
	SKEL_PelvisRoot = 0x45FC,
	SKEL_SADDLE = 0x9524,
	MH_L_CalfBack = 0x1013,
	MH_L_ThighBack = 0x600D,
	SM_L_Skirt = 0xC419,
	MH_R_CalfBack = 0xB013,
	MH_R_ThighBack = 0x51A3,
	SM_R_Skirt = 0x7712,
	SM_M_BackSkirtRoll = 0xDBB,
	SM_L_BackSkirtRoll = 0x40B2,
	SM_R_BackSkirtRoll = 0xC141,
	SM_M_FrontSkirtRoll = 0xCDBB,
	SM_L_FrontSkirtRoll = 0x9B69,
	SM_R_FrontSkirtRoll = 0x86F1,
	SM_CockNBalls_ROOT = 0xC67D,
	SM_CockNBalls = 0x9D34,
	MH_L_Finger00 = 0x8C63,
	MH_L_FingerBulge00 = 0x5FB8,
	MH_L_Finger10 = 0x8C53,
	MH_L_FingerTop00 = 0xA244,
	MH_L_HandSide = 0xC78A,
	MH_Watch = 0x2738,
	MH_L_Sleeve = 0x933C,
	MH_R_Finger00 = 0x2C63,
	MH_R_FingerBulge00 = 0x69B8,
	MH_R_Finger10 = 0x2C53,
	MH_R_FingerTop00 = 0xEF4B,
	MH_R_HandSide = 0x68FB,
	MH_R_Sleeve = 0x92DC,
	FACIAL_jaw = 0xB21,
	FACIAL_underChin = 0x8A95,
	FACIAL_L_underChin = 0x234E,
	FACIAL_chin = 0xB578,
	FACIAL_chinSkinBottom = 0x98BC,
	FACIAL_L_chinSkinBottom = 0x3E8F,
	FACIAL_R_chinSkinBottom = 0x9E8F,
	FACIAL_tongueA = 0x4A7C,
	FACIAL_tongueB = 0x4A7D,
	FACIAL_tongueC = 0x4A7E,
	FACIAL_tongueD = 0x4A7F,
	FACIAL_tongueE = 0x4A80,
	FACIAL_L_tongueE = 0x35F2,
	FACIAL_R_tongueE = 0x2FF2,
	FACIAL_L_tongueD = 0x35F1,
	FACIAL_R_tongueD = 0x2FF1,
	FACIAL_L_tongueC = 0x35F0,
	FACIAL_R_tongueC = 0x2FF0,
	FACIAL_L_tongueB = 0x35EF,
	FACIAL_R_tongueB = 0x2FEF,
	FACIAL_L_tongueA = 0x35EE,
	FACIAL_R_tongueA = 0x2FEE,
	FACIAL_chinSkinTop = 0x7226,
	FACIAL_L_chinSkinTop = 0x3EB3,
	FACIAL_chinSkinMid = 0x899A,
	FACIAL_L_chinSkinMid = 0x4427,
	FACIAL_L_chinSide = 0x4A5E,
	FACIAL_R_chinSkinMid = 0xF5AF,
	FACIAL_R_chinSkinTop = 0xF03B,
	FACIAL_R_chinSide = 0xAA5E,
	FACIAL_R_underChin = 0x2BF4,
	FACIAL_L_lipLowerSDK = 0xB9E1,
	FACIAL_L_lipLowerAnalog = 0x244A,
	FACIAL_L_lipLowerThicknessV = 0xC749,
	FACIAL_L_lipLowerThicknessH = 0xC67B,
	FACIAL_lipLowerSDK = 0x7285,
	FACIAL_lipLowerAnalog = 0xD97B,
	FACIAL_lipLowerThicknessV = 0xC5BB,
	FACIAL_lipLowerThicknessH = 0xC5ED,
	FACIAL_R_lipLowerSDK = 0xA034,
	FACIAL_R_lipLowerAnalog = 0xC2D9,
	FACIAL_R_lipLowerThicknessV = 0xC6E9,
	FACIAL_R_lipLowerThicknessH = 0xC6DB,
	FACIAL_nose = 0x20F1,
	FACIAL_L_nostril = 0x7322,
	FACIAL_L_nostrilThickness = 0xC15F,
	FACIAL_noseLower = 0xE05A,
	FACIAL_L_noseLowerThickness = 0x79D5,
	FACIAL_R_noseLowerThickness = 0x7975,
	FACIAL_noseTip = 0x6A60,
	FACIAL_R_nostril = 0x7922,
	FACIAL_R_nostrilThickness = 0x36FF,
	FACIAL_noseUpper = 0xA04F,
	FACIAL_L_noseUpper = 0x1FB8,
	FACIAL_noseBridge = 0x9BA3,
	FACIAL_L_nasolabialFurrow = 0x5ACA,
	FACIAL_L_nasolabialBulge = 0xCD78,
	FACIAL_L_cheekLower = 0x6907,
	FACIAL_L_cheekLowerBulge1 = 0xE3FB,
	FACIAL_L_cheekLowerBulge2 = 0xE3FC,
	FACIAL_L_cheekInner = 0xE7AB,
	FACIAL_L_cheekOuter = 0x8161,
	FACIAL_L_eyesackLower = 0x771B,
	FACIAL_L_eyeball = 0x1744,
	FACIAL_L_eyelidLower = 0x998C,
	FACIAL_L_eyelidLowerOuterSDK = 0xFE4C,
	FACIAL_L_eyelidLowerOuterAnalog = 0xB9AA,
	FACIAL_L_eyelashLowerOuter = 0xD7F6,
	FACIAL_L_eyelidLowerInnerSDK = 0xF151,
	FACIAL_L_eyelidLowerInnerAnalog = 0x8242,
	FACIAL_L_eyelashLowerInner = 0x4CCF,
	FACIAL_L_eyelidUpper = 0x97C1,
	FACIAL_L_eyelidUpperOuterSDK = 0xAF15,
	FACIAL_L_eyelidUpperOuterAnalog = 0x67FA,
	FACIAL_L_eyelashUpperOuter = 0x27B7,
	FACIAL_L_eyelidUpperInnerSDK = 0xD341,
	FACIAL_L_eyelidUpperInnerAnalog = 0xF092,
	FACIAL_L_eyelashUpperInner = 0x9B1F,
	FACIAL_L_eyesackUpperOuterBulge = 0xA559,
	FACIAL_L_eyesackUpperInnerBulge = 0x2F2A,
	FACIAL_L_eyesackUpperOuterFurrow = 0xC597,
	FACIAL_L_eyesackUpperInnerFurrow = 0x52A7,
	FACIAL_forehead = 0x9218,
	FACIAL_L_foreheadInner = 0x843,
	FACIAL_L_foreheadInnerBulge = 0x767C,
	FACIAL_L_foreheadOuter = 0x8DCB,
	FACIAL_skull = 0x4221,
	FACIAL_foreheadUpper = 0xF7D6,
	FACIAL_L_foreheadUpperInner = 0xCF13,
	FACIAL_L_foreheadUpperOuter = 0x509B,
	FACIAL_R_foreheadUpperInner = 0xCEF3,
	FACIAL_R_foreheadUpperOuter = 0x507B,
	FACIAL_L_temple = 0xAF79,
	FACIAL_L_ear = 0x19DD,
	FACIAL_L_earLower = 0x6031,
	FACIAL_L_masseter = 0x2810,
	FACIAL_L_jawRecess = 0x9C7A,
	FACIAL_L_cheekOuterSkin = 0x14A5,
	FACIAL_R_cheekLower = 0xF367,
	FACIAL_R_cheekLowerBulge1 = 0x599B,
	FACIAL_R_cheekLowerBulge2 = 0x599C,
	FACIAL_R_masseter = 0x810,
	FACIAL_R_jawRecess = 0x93D4,
	FACIAL_R_ear = 0x1137,
	FACIAL_R_earLower = 0x8031,
	FACIAL_R_eyesackLower = 0x777B,
	FACIAL_R_nasolabialBulge = 0xD61E,
	FACIAL_R_cheekOuter = 0xD32,
	FACIAL_R_cheekInner = 0x737C,
	FACIAL_R_noseUpper = 0x1CD6,
	FACIAL_R_foreheadInner = 0xE43,
	FACIAL_R_foreheadInnerBulge = 0x769C,
	FACIAL_R_foreheadOuter = 0x8FCB,
	FACIAL_R_cheekOuterSkin = 0xB334,
	FACIAL_R_eyesackUpperInnerFurrow = 0x9FAE,
	FACIAL_R_eyesackUpperOuterFurrow = 0x140F,
	FACIAL_R_eyesackUpperInnerBulge = 0xA359,
	FACIAL_R_eyesackUpperOuterBulge = 0x1AF9,
	FACIAL_R_nasolabialFurrow = 0x2CAA,
	FACIAL_R_temple = 0xAF19,
	FACIAL_R_eyeball = 0x1944,
	FACIAL_R_eyelidUpper = 0x7E14,
	FACIAL_R_eyelidUpperOuterSDK = 0xB115,
	FACIAL_R_eyelidUpperOuterAnalog = 0xF25A,
	FACIAL_R_eyelashUpperOuter = 0xE0A,
	FACIAL_R_eyelidUpperInnerSDK = 0xD541,
	FACIAL_R_eyelidUpperInnerAnalog = 0x7C63,
	FACIAL_R_eyelashUpperInner = 0x8172,
	FACIAL_R_eyelidLower = 0x7FDF,
	FACIAL_R_eyelidLowerOuterSDK = 0x1BD,
	FACIAL_R_eyelidLowerOuterAnalog = 0x457B,
	FACIAL_R_eyelashLowerOuter = 0xBE49,
	FACIAL_R_eyelidLowerInnerSDK = 0xF351,
	FACIAL_R_eyelidLowerInnerAnalog = 0xE13,
	FACIAL_R_eyelashLowerInner = 0x3322,
	FACIAL_L_lipUpperSDK = 0x8F30,
	FACIAL_L_lipUpperAnalog = 0xB1CF,
	FACIAL_L_lipUpperThicknessH = 0x37CE,
	FACIAL_L_lipUpperThicknessV = 0x38BC,
	FACIAL_lipUpperSDK = 0x1774,
	FACIAL_lipUpperAnalog = 0xE064,
	FACIAL_lipUpperThicknessH = 0x7993,
	FACIAL_lipUpperThicknessV = 0x7981,
	FACIAL_L_lipCornerSDK = 0xB1C,
	FACIAL_L_lipCornerAnalog = 0xE568,
	FACIAL_L_lipCornerThicknessUpper = 0x7BC,
	FACIAL_L_lipCornerThicknessLower = 0xDD42,
	FACIAL_R_lipUpperSDK = 0x7583,
	FACIAL_R_lipUpperAnalog = 0x51CF,
	FACIAL_R_lipUpperThicknessH = 0x382E,
	FACIAL_R_lipUpperThicknessV = 0x385C,
	FACIAL_R_lipCornerSDK = 0xB3C,
	FACIAL_R_lipCornerAnalog = 0xEE0E,
	FACIAL_R_lipCornerThicknessUpper = 0x54C3,
	FACIAL_R_lipCornerThicknessLower = 0x2BBA,
	MH_MulletRoot = 0x3E73,
	MH_MulletScaler = 0xA1C2,
	MH_Hair_Scale = 0xC664,
	MH_Hair_Crown = 0x1675,
	SM_Torch = 0x8D6,
	FX_Light = 0x8959,
	FX_Light_Scale = 0x5038,
	FX_Light_Switch = 0xE18E,
	BagRoot = 0xAD09,
	BagPivotROOT = 0xB836,
	BagPivot = 0x4D11,
	BagBody = 0xAB6D,
	BagBone_R = 0x937,
	BagBone_L = 0x991,
	SM_LifeSaver_Front = 0x9420,
	SM_R_Pouches_ROOT = 0x2962,
	SM_R_Pouches = 0x4141,
	SM_L_Pouches_ROOT = 0x2A02,
	SM_L_Pouches = 0x4B41,
	SM_Suit_Back_Flapper = 0xDA2D,
	SPR_CopRadio = 0x8245,
	SM_LifeSaver_Back = 0x2127,
	MH_BlushSlider = 0xA0CE,
	SKEL_Tail_01 = 0x347,
	SKEL_Tail_02 = 0x348,
	MH_L_Concertina_B = 0xC988,
	MH_L_Concertina_A = 0xC987,
	MH_R_Concertina_B = 0xC8E8,
	MH_R_Concertina_A = 0xC8E7,
	MH_L_ShoulderBladeRoot = 0x8711,
	MH_L_ShoulderBlade = 0x4EAF,
	MH_R_ShoulderBladeRoot = 0x3A0A,
	MH_R_ShoulderBlade = 0x54AF,
	FB_R_Ear_000 = 0x6CDF,
	SPR_R_Ear = 0x63B6,
	FB_L_Ear_000 = 0x6439,
	SPR_L_Ear = 0x5B10,
	FB_TongueA_000 = 0x4206,
	FB_TongueB_000 = 0x4207,
	FB_TongueC_000 = 0x4208,
	SKEL_L_Toe1 = 0x1D6B,
	SKEL_R_Toe1 = 0xB23F,
	SKEL_Tail_03 = 0x349,
	SKEL_Tail_04 = 0x34A,
	SKEL_Tail_05 = 0x34B,
	SPR_Gonads_ROOT = 0xBFDE,
	SPR_Gonads = 0x1C00,
	FB_L_Brow_Out_001 = 0xE3DB,
	FB_L_Lid_Upper_001 = 0xB2B6,
	FB_L_Eye_001 = 0x62AC,
	FB_L_CheekBone_001 = 0x542E,
	FB_L_Lip_Corner_001 = 0x74AC,
	FB_R_Lid_Upper_001 = 0xAA10,
	FB_R_Eye_001 = 0x6B52,
	FB_R_CheekBone_001 = 0x4B88,
	FB_R_Brow_Out_001 = 0x54C,
	FB_R_Lip_Corner_001 = 0x2BA6,
	FB_Brow_Centre_001 = 0x9149,
	FB_UpperLipRoot_001 = 0x4ED2,
	FB_UpperLip_001 = 0xF18F,
	FB_L_Lip_Top_001 = 0x4F37,
	FB_R_Lip_Top_001 = 0x4537,
	FB_Jaw_001 = 0xB4A0,
	FB_LowerLipRoot_001 = 0x4324,
	FB_LowerLip_001 = 0x508F,
	FB_L_Lip_Bot_001 = 0xB93B,
	FB_R_Lip_Bot_001 = 0xC33B,
	FB_Tongue_001 = 0xB987
};
enum VehicleModTypes
{
	MOD_SPOILER = 0,
	MOD_FRONTBUMPER = 1,
	MOD_REARBUMPER = 2,
	MOD_SIDESKIRT = 3,
	MOD_EXHAUST = 4,
	MOD_CHASSIS = 5, // or roll cage
	MOD_GRILLE = 6,
	MOD_HOOD = 7,
	MOD_FENDER = 8,
	MOD_RIGHTFENDER = 9,
	MOD_ROOF = 10,
	MOD_ENGINE = 11,
	MOD_BRAKES = 12,
	MOD_TRANSMISSION = 13,
	MOD_HORNS = 14,
	MOD_SUSPENSION = 15,
	MOD_ARMOR = 16,
	MOD_UNK17 = 17, // ModToggleTurbo use 18
	MOD_TURBO = 18,
	MOD_UNK19 = 19, // ModToggleTireSmoke use 20
	MOD_TIRESMOKE = 20,
	MOD_UNK21 = 21, // ModToggleXenon use 22
	MOD_XENONLIGHTS = 22,
	MOD_FRONTWHEELS = 23,
	MOD_BACKWHEELS = 24, // Bikes only

	// Benny's
	MOD_PLATEHOLDER = 25,
	MOD_VANITY_PLATES = 26,
	MOD_TRIM = 27,
	MOD_ORNAMENTS = 28,
	MOD_DASHBOARD = 29,
	MOD_DIAL = 30,
	MOD_DOOR_SPEAKER = 31,
	MOD_SEATS = 32,
	MOD_STEERINGWHEEL = 33,
	MOD_SHIFTER_LEAVERS = 34,
	MOD_PLAQUES = 35,
	MOD_SPEAKERS = 36,
	MOD_TRUNK = 37,
	MOD_HYDRAULICS = 38,
	MOD_ENGINE_BLOCK = 39,
	MOD_AIR_FILTER = 40,
	MOD_STRUTS = 41,
	MOD_ARCH_COVER = 42,
	MOD_AERIALS = 43,
	MOD_TRIM_2 = 44,
	MOD_TANK = 45,
	MOD_WINDOWS = 46,
	MOD_UNK47 = 47,
	MOD_LIVERY = 48,
};

enum ControllerInputs
{
	INPUT_NEXT_CAMERA,
	INPUT_LOOK_LR,
	INPUT_LOOK_UD,
	INPUT_LOOK_UP_ONLY,
	INPUT_LOOK_DOWN_ONLY,
	INPUT_LOOK_LEFT_ONLY,
	INPUT_LOOK_RIGHT_ONLY,
	INPUT_CINEMATIC_SLOWMO,
	INPUT_SCRIPTED_FLY_UD,
	INPUT_SCRIPTED_FLY_LR,
	INPUT_SCRIPTED_FLY_ZUP,
	INPUT_SCRIPTED_FLY_ZDOWN,
	INPUT_WEAPON_WHEEL_UD,
	INPUT_WEAPON_WHEEL_LR,
	INPUT_WEAPON_WHEEL_NEXT,
	INPUT_WEAPON_WHEEL_PREV,
	INPUT_SELECT_NEXT_WEAPON,
	INPUT_SELECT_PREV_WEAPON,
	INPUT_SKIP_CUTSCENE,
	INPUT_CHARACTER_WHEEL,
	INPUT_MULTIPLAYER_INFO,
	INPUT_SPRINT,
	INPUT_JUMP,
	INPUT_ENTER,
	INPUT_ATTACK,
	INPUT_AIM,
	INPUT_LOOK_BEHIND,
	INPUT_PHONE,
	INPUT_SPECIAL_ABILITY,
	INPUT_SPECIAL_ABILITY_SECONDARY,
	INPUT_MOVE_LR,
	INPUT_MOVE_UD,
	INPUT_MOVE_UP_ONLY,
	INPUT_MOVE_DOWN_ONLY,
	INPUT_MOVE_LEFT_ONLY,
	INPUT_MOVE_RIGHT_ONLY,
	INPUT_DUCK,
	INPUT_SELECT_WEAPON,
	INPUT_PICKUP,
	INPUT_SNIPER_ZOOM,
	INPUT_SNIPER_ZOOM_IN_ONLY,
	INPUT_SNIPER_ZOOM_OUT_ONLY,
	INPUT_SNIPER_ZOOM_IN_SECONDARY,
	INPUT_SNIPER_ZOOM_OUT_SECONDARY,
	INPUT_COVER,
	INPUT_RELOAD,
	INPUT_TALK,
	INPUT_DETONATE,
	INPUT_HUD_SPECIAL,
	INPUT_ARREST,
	INPUT_ACCURATE_AIM,
	INPUT_CONTEXT,
	INPUT_CONTEXT_SECONDARY,
	INPUT_WEAPON_SPECIAL,
	INPUT_WEAPON_SPECIAL_TWO,
	INPUT_DIVE,
	INPUT_DROP_WEAPON,
	INPUT_DROP_AMMO,
	INPUT_THROW_GRENADE,
	INPUT_VEH_MOVE_LR,
	INPUT_VEH_MOVE_UD,
	INPUT_VEH_MOVE_UP_ONLY,
	INPUT_VEH_MOVE_DOWN_ONLY,
	INPUT_VEH_MOVE_LEFT_ONLY,
	INPUT_VEH_MOVE_RIGHT_ONLY,
	INPUT_VEH_SPECIAL,
	INPUT_VEH_GUN_LR,
	INPUT_VEH_GUN_UD,
	INPUT_VEH_AIM,
	INPUT_VEH_ATTACK,
	INPUT_VEH_ATTACK2,
	INPUT_VEH_ACCELERATE,
	INPUT_VEH_BRAKE,
	INPUT_VEH_DUCK,
	INPUT_VEH_HEADLIGHT,
	INPUT_VEH_EXIT,
	INPUT_VEH_HANDBRAKE,
	INPUT_VEH_HOTWIRE_LEFT,
	INPUT_VEH_HOTWIRE_RIGHT,
	INPUT_VEH_LOOK_BEHIND,
	INPUT_VEH_CIN_CAM,
	INPUT_VEH_NEXT_RADIO,
	INPUT_VEH_PREV_RADIO,
	INPUT_VEH_NEXT_RADIO_TRACK,
	INPUT_VEH_PREV_RADIO_TRACK,
	INPUT_VEH_RADIO_WHEEL,
	INPUT_VEH_HORN,
	INPUT_VEH_FLY_THROTTLE_UP,
	INPUT_VEH_FLY_THROTTLE_DOWN,
	INPUT_VEH_FLY_YAW_LEFT,
	INPUT_VEH_FLY_YAW_RIGHT,
	INPUT_VEH_PASSENGER_AIM,
	INPUT_VEH_PASSENGER_ATTACK,
	INPUT_VEH_SPECIAL_ABILITY_FRANKLIN,
	INPUT_VEH_STUNT_UD,
	INPUT_VEH_CINEMATIC_UD,
	INPUT_VEH_CINEMATIC_UP_ONLY,
	INPUT_VEH_CINEMATIC_DOWN_ONLY,
	INPUT_VEH_CINEMATIC_LR,
	INPUT_VEH_SELECT_NEXT_WEAPON,
	INPUT_VEH_SELECT_PREV_WEAPON,
	INPUT_VEH_ROOF,
	INPUT_VEH_JUMP,
	INPUT_VEH_GRAPPLING_HOOK,
	INPUT_VEH_SHUFFLE,
	INPUT_VEH_DROP_PROJECTILE,
	INPUT_VEH_MOUSE_CONTROL_OVERRIDE,
	INPUT_VEH_FLY_ROLL_LR,
	INPUT_VEH_FLY_ROLL_LEFT_ONLY,
	INPUT_VEH_FLY_ROLL_RIGHT_ONLY,
	INPUT_VEH_FLY_PITCH_UD,
	INPUT_VEH_FLY_PITCH_UP_ONLY,
	INPUT_VEH_FLY_PITCH_DOWN_ONLY,
	INPUT_VEH_FLY_UNDERCARRIAGE,
	INPUT_VEH_FLY_ATTACK,
	INPUT_VEH_FLY_SELECT_NEXT_WEAPON,
	INPUT_VEH_FLY_SELECT_PREV_WEAPON,
	INPUT_VEH_FLY_SELECT_TARGET_LEFT,
	INPUT_VEH_FLY_SELECT_TARGET_RIGHT,
	INPUT_VEH_FLY_VERTICAL_FLIGHT_MODE,
	INPUT_VEH_FLY_DUCK,
	INPUT_VEH_FLY_ATTACK_CAMERA,
	INPUT_VEH_FLY_MOUSE_CONTROL_OVERRIDE,
	INPUT_VEH_SUB_TURN_LR,
	INPUT_VEH_SUB_TURN_LEFT_ONLY,
	INPUT_VEH_SUB_TURN_RIGHT_ONLY,
	INPUT_VEH_SUB_PITCH_UD,
	INPUT_VEH_SUB_PITCH_UP_ONLY,
	INPUT_VEH_SUB_PITCH_DOWN_ONLY,
	INPUT_VEH_SUB_THROTTLE_UP,
	INPUT_VEH_SUB_THROTTLE_DOWN,
	INPUT_VEH_SUB_ASCEND,
	INPUT_VEH_SUB_DESCEND,
	INPUT_VEH_SUB_TURN_HARD_LEFT,
	INPUT_VEH_SUB_TURN_HARD_RIGHT,
	INPUT_VEH_SUB_MOUSE_CONTROL_OVERRIDE,
	INPUT_VEH_PUSHBIKE_PEDAL,
	INPUT_VEH_PUSHBIKE_SPRINT,
	INPUT_VEH_PUSHBIKE_FRONT_BRAKE,
	INPUT_VEH_PUSHBIKE_REAR_BRAKE,
	INPUT_MELEE_ATTACK_LIGHT,
	INPUT_MELEE_ATTACK_HEAVY,
	INPUT_MELEE_ATTACK_ALTERNATE,
	INPUT_MELEE_BLOCK,
	INPUT_PARACHUTE_DEPLOY,
	INPUT_PARACHUTE_DETACH,
	INPUT_PARACHUTE_TURN_LR,
	INPUT_PARACHUTE_TURN_LEFT_ONLY,
	INPUT_PARACHUTE_TURN_RIGHT_ONLY,
	INPUT_PARACHUTE_PITCH_UD,
	INPUT_PARACHUTE_PITCH_UP_ONLY,
	INPUT_PARACHUTE_PITCH_DOWN_ONLY,
	INPUT_PARACHUTE_BRAKE_LEFT,
	INPUT_PARACHUTE_BRAKE_RIGHT,
	INPUT_PARACHUTE_SMOKE,
	INPUT_PARACHUTE_PRECISION_LANDING,
	INPUT_MAP,
	INPUT_SELECT_WEAPON_UNARMED,
	INPUT_SELECT_WEAPON_MELEE,
	INPUT_SELECT_WEAPON_HANDGUN,
	INPUT_SELECT_WEAPON_SHOTGUN,
	INPUT_SELECT_WEAPON_SMG,
	INPUT_SELECT_WEAPON_AUTO_RIFLE,
	INPUT_SELECT_WEAPON_SNIPER,
	INPUT_SELECT_WEAPON_HEAVY,
	INPUT_SELECT_WEAPON_SPECIAL,
	INPUT_SELECT_CHARACTER_MICHAEL,
	INPUT_SELECT_CHARACTER_FRANKLIN,
	INPUT_SELECT_CHARACTER_TREVOR,
	INPUT_SELECT_CHARACTER_MULTIPLAYER,
	INPUT_SAVE_REPLAY_CLIP,
	INPUT_SPECIAL_ABILITY_PC,
	INPUT_CELLPHONE_UP,
	INPUT_CELLPHONE_DOWN,
	INPUT_CELLPHONE_LEFT,
	INPUT_CELLPHONE_RIGHT,
	INPUT_CELLPHONE_SELECT,
	INPUT_CELLPHONE_CANCEL,
	INPUT_CELLPHONE_OPTION,
	INPUT_CELLPHONE_EXTRA_OPTION,
	INPUT_CELLPHONE_SCROLL_FORWARD,
	INPUT_CELLPHONE_SCROLL_BACKWARD,
	INPUT_CELLPHONE_CAMERA_FOCUS_LOCK,
	INPUT_CELLPHONE_CAMERA_GRID,
	INPUT_CELLPHONE_CAMERA_SELFIE,
	INPUT_CELLPHONE_CAMERA_DOF,
	INPUT_CELLPHONE_CAMERA_EXPRESSION,
	INPUT_FRONTEND_DOWN,
	INPUT_FRONTEND_UP,
	INPUT_FRONTEND_LEFT,
	INPUT_FRONTEND_RIGHT,
	INPUT_FRONTEND_RDOWN,
	INPUT_FRONTEND_RUP,
	INPUT_FRONTEND_RLEFT,
	INPUT_FRONTEND_RRIGHT,
	INPUT_FRONTEND_AXIS_X,
	INPUT_FRONTEND_AXIS_Y,
	INPUT_FRONTEND_RIGHT_AXIS_X,
	INPUT_FRONTEND_RIGHT_AXIS_Y,
	INPUT_FRONTEND_PAUSE,
	INPUT_FRONTEND_PAUSE_ALTERNATE,
	INPUT_FRONTEND_ACCEPT,
	INPUT_FRONTEND_CANCEL,
	INPUT_FRONTEND_X,
	INPUT_FRONTEND_Y,
	INPUT_FRONTEND_LB,
	INPUT_FRONTEND_RB,
	INPUT_FRONTEND_LT,
	INPUT_FRONTEND_RT,
	INPUT_FRONTEND_LS,
	INPUT_FRONTEND_RS,
	INPUT_FRONTEND_LEADERBOARD,
	INPUT_FRONTEND_SOCIAL_CLUB,
	INPUT_FRONTEND_SOCIAL_CLUB_SECONDARY,
	INPUT_FRONTEND_DELETE,
	INPUT_FRONTEND_ENDSCREEN_ACCEPT,
	INPUT_FRONTEND_ENDSCREEN_EXPAND,
	INPUT_FRONTEND_SELECT,
	INPUT_SCRIPT_LEFT_AXIS_X,
	INPUT_SCRIPT_LEFT_AXIS_Y,
	INPUT_SCRIPT_RIGHT_AXIS_X,
	INPUT_SCRIPT_RIGHT_AXIS_Y,
	INPUT_SCRIPT_RUP,
	INPUT_SCRIPT_RDOWN,
	INPUT_SCRIPT_RLEFT,
	INPUT_SCRIPT_RRIGHT,
	INPUT_SCRIPT_LB,
	INPUT_SCRIPT_RB,
	INPUT_SCRIPT_LT,
	INPUT_SCRIPT_RT,
	INPUT_SCRIPT_LS,
	INPUT_SCRIPT_RS,
	INPUT_SCRIPT_PAD_UP,
	INPUT_SCRIPT_PAD_DOWN,
	INPUT_SCRIPT_PAD_LEFT,
	INPUT_SCRIPT_PAD_RIGHT,
	INPUT_SCRIPT_SELECT,
	INPUT_CURSOR_ACCEPT,
	INPUT_CURSOR_CANCEL,
	INPUT_CURSOR_X,
	INPUT_CURSOR_Y,
	INPUT_CURSOR_SCROLL_UP,
	INPUT_CURSOR_SCROLL_DOWN,
	INPUT_ENTER_CHEAT_CODE,
	INPUT_INTERACTION_MENU,
	INPUT_MP_TEXT_CHAT_ALL,
	INPUT_MP_TEXT_CHAT_TEAM,
	INPUT_MP_TEXT_CHAT_FRIENDS,
	INPUT_MP_TEXT_CHAT_CREW,
	INPUT_PUSH_TO_TALK,
	INPUT_CREATOR_LS,
	INPUT_CREATOR_RS,
	INPUT_CREATOR_LT,
	INPUT_CREATOR_RT,
	INPUT_CREATOR_MENU_TOGGLE,
	INPUT_CREATOR_ACCEPT,
	INPUT_CREATOR_DELETE,
	INPUT_ATTACK2,
	INPUT_RAPPEL_JUMP,
	INPUT_RAPPEL_LONG_JUMP,
	INPUT_RAPPEL_SMASH_WINDOW,
	INPUT_PREV_WEAPON,
	INPUT_NEXT_WEAPON,
	INPUT_MELEE_ATTACK1,
	INPUT_MELEE_ATTACK2,
	INPUT_WHISTLE,
	INPUT_MOVE_LEFT,
	INPUT_MOVE_RIGHT,
	INPUT_MOVE_UP,
	INPUT_MOVE_DOWN,
	INPUT_LOOK_LEFT,
	INPUT_LOOK_RIGHT,
	INPUT_LOOK_UP,
	INPUT_LOOK_DOWN,
	INPUT_SNIPER_ZOOM_IN,
	INPUT_SNIPER_ZOOM_OUT,
	INPUT_SNIPER_ZOOM_IN_ALTERNATE,
	INPUT_SNIPER_ZOOM_OUT_ALTERNATE,
	INPUT_VEH_MOVE_LEFT,
	INPUT_VEH_MOVE_RIGHT,
	INPUT_VEH_MOVE_UP,
	INPUT_VEH_MOVE_DOWN,
	INPUT_VEH_GUN_LEFT,
	INPUT_VEH_GUN_RIGHT,
	INPUT_VEH_GUN_UP,
	INPUT_VEH_GUN_DOWN,
	INPUT_VEH_LOOK_LEFT,
	INPUT_VEH_LOOK_RIGHT,
	INPUT_REPLAY_START_STOP_RECORDING,
	INPUT_REPLAY_START_STOP_RECORDING_SECONDARY,
	INPUT_SCALED_LOOK_LR,
	INPUT_SCALED_LOOK_UD,
	INPUT_SCALED_LOOK_UP_ONLY,
	INPUT_SCALED_LOOK_DOWN_ONLY,
	INPUT_SCALED_LOOK_LEFT_ONLY,
	INPUT_SCALED_LOOK_RIGHT_ONLY,
	INPUT_REPLAY_MARKER_DELETE,
	INPUT_REPLAY_CLIP_DELETE,
	INPUT_REPLAY_PAUSE,
	INPUT_REPLAY_REWIND,
	INPUT_REPLAY_FFWD,
	INPUT_REPLAY_NEWMARKER,
	INPUT_REPLAY_RECORD,
	INPUT_REPLAY_SCREENSHOT,
	INPUT_REPLAY_HIDEHUD,
	INPUT_REPLAY_STARTPOINT,
	INPUT_REPLAY_ENDPOINT,
	INPUT_REPLAY_ADVANCE,
	INPUT_REPLAY_BACK,
	INPUT_REPLAY_TOOLS,
	INPUT_REPLAY_RESTART,
	INPUT_REPLAY_SHOWHOTKEY,
	INPUT_REPLAY_CYCLEMARKERLEFT,
	INPUT_REPLAY_CYCLEMARKERRIGHT,
	INPUT_REPLAY_FOVINCREASE,
	INPUT_REPLAY_FOVDECREASE,
	INPUT_REPLAY_CAMERAUP,
	INPUT_REPLAY_CAMERADOWN,
	INPUT_REPLAY_SAVE,
	INPUT_REPLAY_TOGGLETIME,
	INPUT_REPLAY_TOGGLETIPS,
	INPUT_REPLAY_PREVIEW,
	INPUT_REPLAY_TOGGLE_TIMELINE,
	INPUT_REPLAY_TIMELINE_PICKUP_CLIP,
	INPUT_REPLAY_TIMELINE_DUPLICATE_CLIP,
	INPUT_REPLAY_TIMELINE_PLACE_CLIP,
	INPUT_REPLAY_CTRL,
	INPUT_REPLAY_TIMELINE_SAVE,
	INPUT_REPLAY_PREVIEW_AUDIO,
	INPUT_VEH_DRIVE_LOOK,
	INPUT_VEH_DRIVE_LOOK2,
	INPUT_VEH_FLY_ATTACK2,
	INPUT_RADIO_WHEEL_UD,
	INPUT_RADIO_WHEEL_LR,
	INPUT_VEH_SLOWMO_UD,
	INPUT_VEH_SLOWMO_UP_ONLY,
	INPUT_VEH_SLOWMO_DOWN_ONLY,
	INPUT_VEH_HYDRAULICS_CONTROL_TOGGLE,
	INPUT_VEH_HYDRAULICS_CONTROL_LEFT,
	INPUT_VEH_HYDRAULICS_CONTROL_RIGHT,
	INPUT_VEH_HYDRAULICS_CONTROL_UP,
	INPUT_VEH_HYDRAULICS_CONTROL_DOWN,
	INPUT_VEH_HYDRAULICS_CONTROL_LR,
	INPUT_VEH_HYDRAULICS_CONTROL_UD,
	INPUT_SWITCH_VISOR,
	INPUT_VEH_MELEE_HOLD,
	INPUT_VEH_MELEE_LEFT,
	INPUT_VEH_MELEE_RIGHT,
	INPUT_MAP_POI,
	INPUT_REPLAY_SNAPMATIC_PHOTO,
	INPUT_VEH_CAR_JUMP,
	INPUT_VEH_ROCKET_BOOST,
	INPUT_VEH_FLY_BOOST,
	INPUT_VEH_PARACHUTE,
	INPUT_VEH_BIKE_WINGS,
	INPUT_VEH_FLY_BOMB_BAY,
	INPUT_VEH_FLY_COUNTER,
	INPUT_VEH_TRANSFORM,
	MAX_INPUTS,
	UNDEFINED_INPUT,
	DYNAMIC_MAPPING_MOUSE_X,
	DYNAMIC_MAPPING_MOUSE_Y,
	FIRST_INPUT,
	SCRIPTED_INPUT_FIRST,
	SCRIPTED_INPUT_LAST
};
