[unit
	id = Stnk
	[text
		unit_name = string:"SOTM Light Tank"
		description = string:"SOTM main battle unit. It is propelled by a hover drive, which gives the tank very high mobility."
	]
	[visual
		model_name = string:"sotank.obj"
	]
	[gui
		selection_shape = string:"sotank.hdf"
	]
	[movement
		type = hover // acceptable types: ground, wheeled, tracked, hover
		height = float:0.775
		speed = float:25.0 //20.0
		acceleration = float:5.0
		turn_speed = float:360.0
		can_reverse = bool:false
	]
	[combat
		hitpoints = float:1800.0
	]
]
[unit
	id = Btnk
	[text
		unit_name = string:"Buhlotank"
		description = string:"A lot of reutilized scrap metal"
	]
	[visual
		model_name = string:"butank.obj"
	]
	[gui
		selection_shape = string:"butank.hdf"
	]
	[movement
		type = ground
		speed = float:11.5 //20.0
		acceleration = float:5.0
		turn_speed = float:180.0
		can_reverse = bool:false
	]
	[combat
		hitpoints = float:1800.0
	]
]
[unit
	id = Btrk
	[text
		unit_name = string:"Buhlotank"
		description = string:"A lot of reutilized scrap metal"
	]
	[visual
		model_name = string:"butruck.obj"
	]
	[gui
		selection_shape = string:"butruck.hdf"
	]
	[movement
		type = wheeled
		speed = float:17.0 //20.0
		acceleration = float:5.0
		turn_speed = float:270.0
		can_reverse = bool:false
	]
	[combat
		hitpoints = float:1800.0
	]
]
[unit
	id = Btsp
	[text
		unit_name = string:"Buhlotank"
		description = string:"A lot of reutilized scrap metal"
	]
	[visual
		model_name = string:"butransport.obj"
	]
	[gui
		selection_shape = string:"butruck.hdf"
	]
	[movement
		type = wheeled
		speed = float:17.0 //20.0
		acceleration = float:5.0
		turn_speed = float:270.0
		can_reverse = bool:false
	]
	[combat
		hitpoints = float:1800.0
	]
]
[unit
	id = Crat
	[text
		unit_name = string:"Buhlotank"
		description = string:"A lot of reutilized scrap metal"
	]
	[visual
		model_name = string:"crate10x10.3DS"
	]
	[gui
		selection_shape = string:"butruck.hdf"
	]
	[movement
		type = wheeled
		speed = float:10.0 //20.0
		acceleration = float:5.0
		turn_speed = float:270.0
		can_reverse = bool:false
	]
	[combat
		hitpoints = float:1800.0
	]
]


//hrengin::u32 defaultShape = app.phymgr.loadModel("sphere5.hdf");
