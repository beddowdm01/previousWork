//set camera
var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera( 45, window.innerWidth / window.innerHeight, 0.1, 1000 ); // Perspective projection parameters


var renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight); // Size of the 2D projection
document.body.appendChild(renderer.domElement); // Connecting to the canvas
renderer.shadowMap.enabled = true;// Rendering shadow
renderer.shadowMap.type = THREE.PCFSoftShadowMap;

var effect = new THREE.StereoEffect( renderer );
effect.setSize( window.innerWidth, window.innerHeight );

//set controls
var controls = new THREE.DeviceOrientationControls(camera);
camera.position.set(0, 10, 30); //camera position
controls.enableDamping = true;
controls.dampingFactor = 0.25;
controls.screenSpacePanning = false; 
controls.keys = {
	LEFT: 37,
	UP: 38,
	RIGHT: 39,
	BOTTOM: 40
}


//Earth material and mesh
var earthgeo = new THREE.DodecahedronGeometry(5, 1);
var earthMat = new THREE.MeshPhongMaterial({color: 0x5cc1e0, flatShading: true, shininess: 100 });
var earth = new THREE.Mesh (earthgeo, earthMat);
earth.name = 'earth';

//initialise loader
var loader = new THREE.TextureLoader();

//initialise variable sun
var sun;
loader.load(
    // resource URL
    'textures/sun.jpg',
    // Function when resource is loaded – a callback function
    function ( texture ) {
        //create a mesh using sphere geometry
        var sunGeo = new THREE.SphereGeometry(6, 16, 16);
        var sunMat = new THREE.MeshBasicMaterial( { map: texture } );
        sun = new THREE.Mesh (sunGeo, sunMat);
        sun.position.x = 20; //set the position of the sun
        sun.name = "sun"; //give variable sun a string name for checking intersection
        scene.add(sun); // add the mesh to the scene
        sun.parent = sunLight; //set parent to sunLight
    },
    // Function called when download progresses 
    function ( xhr ) {
        console.log( (xhr.loaded / xhr.total * 100) + '% loaded' );
    },
    // Function called when download errors – a callback function
    function ( xhr ) {
        console.log( 'An error happened' );
    }
);


// skybox
var path = "textures/";
var format = '.jpg';
var urls = [
	path + 'xz' + format, path + 'yy' + format,
	path + 'xx' + format, path + 'yx' + format,
	path + 'yz' + format, path + 'xy' + format
];//gets all the texture paths
var refractionCube = new THREE.CubeTextureLoader().load( urls );
refractionCube.minFilter = THREE.LinearFilter;
refractionCube.format = THREE.RGBFormat;

scene.background = refractionCube;//sets the scene background


//initialise variable moon
var moon;
loader.load(
    // resource URL
   'textures/moon.jpg',
    // Function when resource is loaded – a callback function
    function ( texture ) {
        // then, create a mesh using box geometry with the new material
         var material = new THREE.MeshPhongMaterial( {
            map: texture,
            bumpMap: new THREE.TextureLoader().load('textures/moonbump.jpg')
         } );
		 
        moon = new THREE.Mesh(new THREE.SphereGeometry(3, 16, 16), material);
        moon.position.x = 45; //set position of the moon
        moon.castShadow = true; //cast moon shadow
        moon.receiveShadow = true;
        moon.name = "moon"; //give variable smoon a string name for checking intersection
        scene.add(moon); // add the mesh to the scene
        moon.parent = earth; //set parent to earth
    },
    // Function called when download progresses 
    function ( xhr ) {
        console.log( (xhr.loaded / xhr.total * 100) + '% loaded' );
    },
    // Function called when download errors – a callback function
    function ( xhr ) {
        console.log( 'An error happened' );
    }
);

//cube1 play button
var cube1 = null;
// load a resource
loader.load(
    // resource URL
    'textures/play.png',
    // Function when resource is loaded
    function ( texture ) {
        // create new texture
        var material = new THREE.MeshPhongMaterial( {
            map: texture,
            bumpMap: new THREE.TextureLoader().load('textures/playNorm.png')
         } );

         cube1 = new THREE.Mesh(new THREE.BoxGeometry(2, 2, 2), material);
         cube1.material.side = THREE.DoubleSide; //set material to double sided
         cube1.position.y = -7; //set position y
         cube1.position.x = -3; //set position x
         cube1.name = "cube1";	//give variable cube1 a string name for checking intersection	 
         scene.add(cube1); //add cube1 to the scene

    },
    // Function called when download progresses
    function ( xhr ) {
        console.log( (xhr.loaded / xhr.total * 100) + '% loaded' );
    },
    // Function called when download errors
    function ( xhr ) {
        console.log( 'An error happened' );
    }
);

//cube2 snow button
var cube2 = null;
// load a resource
loader.load(
    // resource URL
    'textures/snow.png',
    // Function when resource is loaded
    function ( texture ) {
        // do something with the texture
        var material = new THREE.MeshPhongMaterial( {
            map: texture,
            bumpMap: new THREE.TextureLoader().load('textures/snowNorm.png')
         } );

         cube2 = new THREE.Mesh(new THREE.BoxGeometry(2, 2, 2), material);
         cube2.material.side = THREE.DoubleSide; //set material to double sided
         cube2.position.y = -7; //set position y
		 cube2.name = "cube2"; //give variable cube2 a string name for checking intersection
         scene.add(cube2); //add cube2 to the scene

    },
    // Function called when download progresses
    function ( xhr ) {
        console.log( (xhr.loaded / xhr.total * 100) + '% loaded' );
    },
    // Function called when download errors
    function ( xhr ) {
        console.log( 'An error happened' );
    }
);

//cube3 rain
var cube3 = null;
// load a resource
loader.load(
    // resource URL
    'textures/volcano.png',
    // Function when resource is loaded
    function ( texture ) {
        // do something with the texture
        var material = new THREE.MeshPhongMaterial( {
            map: texture,
            bumpMap: new THREE.TextureLoader().load('textures/volcanoNorm.png')
         } );

         cube3 = new THREE.Mesh(new THREE.BoxGeometry(2, 2, 2), material);
         cube3.material.side = THREE.DoubleSide; //set material to double sided
         cube3.position.y = -7; //set position y
         cube3.position.x = 3; //set position x
		 cube3.name = "cube3";	//give variable cube3 a string name for checking intersection	 
         scene.add(cube3); //add cube3 to the scene

    },
    // Function called when download progresses
    function ( xhr ) {
        console.log( (xhr.loaded / xhr.total * 100) + '% loaded' );
    },
    // Function called when download errors
    function ( xhr ) {
        console.log( 'An error happened' );
    }
);

//initialise variable tornado
var tornado = null;
var tornadoGeo = new THREE.ConeGeometry(0.5, 1, 6, 20, false); 
tornadoGeo.verticesNeedUpdate = true;
twisting(tornadoGeo, 1);
var m = new THREE.MeshPhongMaterial( {color: 0xCCCCCC, transparent: true, opacity: 0.7 } );

//function for twisting effect
function twisting(geometry, degree) { 
    const quaternion = new THREE.Quaternion();
    for (var i = 0; i < geometry.vertices.length; i++) 
    {
        const yPos = geometry.vertices[i].y;
        const upVec = new THREE.Vector3(0, 1, 0);
        quaternion.setFromAxisAngle(upVec, (Math.PI/180)*degree*yPos);
        geometry.vertices[i].applyQuaternion(quaternion);
    }
    geometry.verticesNeedUpdate = true;
    geometry.computeVertexNormals();
}
tornado = new THREE.Mesh(tornadoGeo, m);
scene.add(tornado);
tornado.rotation.x = 3.14159; // set roation x
tornado.rotation.z = 0.75; // set rotation z
tornado.rotation.y = 0.75; // set rotation y
tornado.position.set(3,2.4,2.4); //set position x, y, z

//sunlight casting shadow
var sunLight = new THREE.PointLight(0xffffff);
sunLight.position.x = 80;
sunLight.intensity = 0.8;
sunLight.castShadow = true;
sunLight.shadow.mapSize.width = 4096;
sunLight.shadow.mapSize.height = 4096;
sunLight.shadow.camera.near = 0.5;
sunLight.shadow.camera.far = 500;
sunLight.shadow.radius = 5.0;
sunLight.shadowCameraVisible = true;


//land1 grass
var land1Geo = new THREE.DodecahedronGeometry(4, 1);
var land1Mat = new THREE.MeshPhongMaterial({color: 0x6aea3f, flatShading: true});
var land1 = new THREE.Mesh (land1Geo, land1Mat);
land1.position.z = 1.21; //set position z
land1.position.y = 0.5; //set position y

//TreeLog Geometry and Meaterial 
var treeLogGeo = new THREE.CylinderGeometry( 0.08, 0.08, 0.4, 7 );
var treeLogMat = new THREE.MeshBasicMaterial( {color: 0x605411, flatShading: true});

//TreeLeaf Geometry and Material 
var treeLeafGeo = new THREE.IcosahedronGeometry( 0.2, 1);
var treeLeafMat = new THREE.MeshBasicMaterial( {color: 0x245604, flatShading: true} );

//Tree1Log
var tree1Log = new THREE.Mesh( treeLogGeo, treeLogMat );
tree1Log.position.z = 3.6;
tree1Log.position.y = 1;
tree1Log.position.x = -1;
tree1Log.rotation.x = 1.5;
tree1Log.rotation.z = 0.3;

//Tree1Leaf
var tree1Leaf= new THREE.Mesh( treeLeafGeo, treeLeafMat );
tree1Leaf.position.y = 0.2;

//Tree2Log
var tree2Log = new THREE.Mesh( treeLogGeo, treeLogMat );
tree2Log.position.z = 1.7;
tree2Log.position.y = 1;
tree2Log.position.x = 4;
tree2Log.rotation.x = 1.1;
tree2Log.rotation.z = -0.8;

//Tree2Leaf
var tree2Leaf= new THREE.Mesh( treeLeafGeo, treeLeafMat );
tree2Leaf.position.y = 0.2;

//Tree3Log
var tree3Log = new THREE.Mesh( treeLogGeo, treeLogMat );
tree3Log.position.z = 0.9;
tree3Log.position.y = 1.2;
tree3Log.position.x = 4.35;
tree3Log.rotation.x = 1.1;
tree3Log.rotation.z = -1.5;

//Tree3Leaf
var tree3Leaf= new THREE.Mesh( treeLeafGeo, treeLeafMat );
tree3Leaf.position.y = 0.2;

//Tree4Log
var tree4Log = new THREE.Mesh( treeLogGeo, treeLogMat );
tree4Log.position.z = 1.5;
tree4Log.position.y = 0.6;
tree4Log.position.x = 4.35;
tree4Log.rotation.x = 1.1;
tree4Log.rotation.z = -1.2;

//Tree4Leaf
var tree4Leaf= new THREE.Mesh( treeLeafGeo, treeLeafMat );
tree4Leaf.position.y = 0.2;

//Tree5Log
var tree5Log = new THREE.Mesh( treeLogGeo, treeLogMat );
tree5Log.position.z = 1.3;
tree5Log.position.y = 1.5;
tree5Log.position.x = 4.1;
tree5Log.rotation.x = 1.1;
tree5Log.rotation.z = -0.8;

//Tree5Leaf
var tree5Leaf= new THREE.Mesh( treeLeafGeo, treeLeafMat );
tree5Leaf.position.y = 0.2;

//Tree6Log
var tree6Log = new THREE.Mesh( treeLogGeo, treeLogMat );
tree6Log.position.z = 3.55;
tree6Log.position.y = 1.5;
tree6Log.position.x = -0.7;
tree6Log.rotation.x = 1.5;
tree6Log.rotation.z = 0.3;

//Tree6Leaf
var tree6Leaf= new THREE.Mesh( treeLeafGeo, treeLeafMat );
tree6Leaf.position.y = 0.2;

//Tree7Log
var tree7Log = new THREE.Mesh( treeLogGeo, treeLogMat );
tree7Log.position.z = 3.7;
tree7Log.position.y = 1;
tree7Log.position.x = -0.5;
tree7Log.rotation.x = 1.4;
tree7Log.rotation.z = 0.3;

//Tree7Leaf
var tree7Leaf= new THREE.Mesh( treeLeafGeo, treeLeafMat );
tree7Leaf.position.y = 0.2;

//cloud type1
var CloudT1Geo = new THREE.DodecahedronGeometry(0.3, 0);
var CloudT1Mat = new THREE.MeshPhongMaterial({color: 0xfffce8, flatShading: true ,transparent: true, opacity: 0.7});

//cloud type2
var CloudT2Geo = new THREE.DodecahedronGeometry(0.4, 0);
var CloudT2Mat = new THREE.MeshPhongMaterial({color: 0xfffce8, flatShading: true ,transparent: true, opacity: 0.7});

//Cloud1 
var Cloud1M = new THREE.Mesh(CloudT2Geo, CloudT2Mat);
var Cloud1L = new THREE.Mesh(CloudT1Geo, CloudT1Mat);
var Cloud1R = new THREE.Mesh(CloudT1Geo, CloudT1Mat);
Cloud1M.position.z = 5;
Cloud1M.position.y = 1;
Cloud1L.position.x = -0.3;
Cloud1R.position.x = 0.3;

//Cloud2 
var Cloud2M = new THREE.Mesh(CloudT2Geo, CloudT2Mat);
var Cloud2L = new THREE.Mesh(CloudT1Geo, CloudT1Mat);
var Cloud2R = new THREE.Mesh(CloudT1Geo, CloudT1Mat);
Cloud2M.position.z = 4.5;
Cloud2M.position.y = 2;
Cloud2M.position.x = 1;
Cloud2M.rotation.y = 0.3;
Cloud2L.position.x = -0.3;
Cloud2R.position.x = 0.3;

//Cloud3
var Cloud3M = new THREE.Mesh(CloudT2Geo, CloudT2Mat);
var Cloud3L = new THREE.Mesh(CloudT1Geo, CloudT1Mat);
var Cloud3R = new THREE.Mesh(CloudT1Geo, CloudT1Mat);
Cloud3M.position.z = 4.5;
Cloud3M.position.y = 1;
Cloud3M.position.x = 2;
Cloud3M.rotation.y = 0.3;
Cloud3L.position.x = -0.3;
Cloud3R.position.x = 0.3;

//Cloud4
var Cloud4M = new THREE.Mesh(CloudT2Geo, CloudT2Mat);
var Cloud4L = new THREE.Mesh(CloudT1Geo, CloudT1Mat);
var Cloud4R = new THREE.Mesh(CloudT1Geo, CloudT1Mat);
Cloud4M.position.z = -4.5;
Cloud4M.position.y = 1;
Cloud4M.position.x = 2;
Cloud4M.rotation.y = -0.1;
Cloud4M.rotation.z = -0.5;
Cloud4L.position.x = -0.3;
Cloud4R.position.x = 0.3;

//Cloud5
var Cloud5M = new THREE.Mesh(CloudT2Geo, CloudT2Mat);
var Cloud5L = new THREE.Mesh(CloudT1Geo, CloudT1Mat);
var Cloud5R = new THREE.Mesh(CloudT1Geo, CloudT1Mat);
Cloud5M.position.z = -4.1;
Cloud5M.position.y = 2;
Cloud5M.position.x = 1;
Cloud5M.rotation.y = -0.1;
Cloud5M.rotation.z = -0.5;
Cloud5L.position.x = -0.3;
Cloud5R.position.x = 0.3;

//Cloud6
var Cloud6M = new THREE.Mesh(CloudT2Geo, CloudT2Mat);
var Cloud6L = new THREE.Mesh(CloudT1Geo, CloudT1Mat);
var Cloud6R = new THREE.Mesh(CloudT1Geo, CloudT1Mat);
Cloud6M.position.z = -3;
Cloud6M.position.y = 2.5;
Cloud6M.position.x = 1;
Cloud6M.rotation.y = 0.7;
Cloud6M.rotation.z = -0.5;
Cloud6L.position.x = -0.3;
Cloud6R.position.x = 0.3;

//Cloud7
var Cloud7M = new THREE.Mesh(CloudT2Geo, CloudT2Mat);
var Cloud7L = new THREE.Mesh(CloudT1Geo, CloudT1Mat);
var Cloud7R = new THREE.Mesh(CloudT1Geo, CloudT1Mat);
Cloud7M.position.z = -2;
Cloud7M.position.y = 3.2;
Cloud7M.position.x = 1;
Cloud7M.rotation.y = 0.7;
Cloud7M.rotation.z = -0.5;
Cloud7L.position.x = -0.3;
Cloud7R.position.x = 0.3;

//land2 grass
var land2Geo = new THREE.DodecahedronGeometry(3.5, 1);
var land2Mat = new THREE.MeshPhongMaterial({color: 0x6aea3f, flatShading: true});
var land2 = new THREE.Mesh (land2Geo, land2Mat);
land2.position.z = -0.05;
land2.position.y = -0.1;
land2.position.x = 1.3;
land2.rotation.z = 0.5;

//land3 dessert
var land3Geo = new THREE.DodecahedronGeometry(4, 1);
var land3Mat = new THREE.MeshPhongMaterial({color: 0xd8ab41, flatShading: true});
var land3 = new THREE.Mesh (land3Geo, land3Mat);
land3.position.x = -1.5;
land3.position.z = -1.8;
land3.position.y = -1;

//volcano
var volcanoGeo = new THREE.CylinderGeometry(0.5, 1.5,1,11,5);
var volcanoMat = new THREE.MeshPhongMaterial({color: 0xd8ab41, flatShading: true})
var volcano = new THREE.Mesh (volcanoGeo, volcanoMat);
volcano.position.x = -0.1;
volcano.position.y = -3;
volcano.position.z = -2.2;
volcano.rotation.x = 3.6;

// lava
var lavaGeo = new THREE.CircleGeometry( 0.3, 32 );
var lavaMat = new THREE.MeshBasicMaterial( { color: 0xf96005, flatShading: true } );
var lava = new THREE.Mesh( lavaGeo, lavaMat );
lava.position.y = 0.51;
lava.rotation.x = -1.6;

//land4 snow
var land4Geo = new THREE.DodecahedronGeometry(4, 1);
var land4Mat = new THREE.MeshPhongMaterial({color: 0xfff9ed, flatShading: true, shininess: 100});
land1Geo.computeFaceNormals();
var land4 = new THREE.Mesh (land4Geo, land4Mat);
land4.position.x = 1;
land4.position.y = 2;
land4.position.z = -0.40;

//land5 snow2
var land5Geo = new THREE.DodecahedronGeometry(3, 1);
var land5Mat = new THREE.MeshPhongMaterial({color: 0xfff9ed, flatShading: true, shininess: 100});
var land5 = new THREE.Mesh (land5Geo, land5Mat);
land5.position.x = -1.2;
land5.position.y = 1.5;

//snow man bottom part
var snowManBottGeo = new THREE.IcosahedronGeometry( 0.2, 1);
var snowManBottMat = new THREE.MeshBasicMaterial( {color: 0xf7f3dc, flatShading: true} );

//snow man head part
var snowManHeadGeo = new THREE.IcosahedronGeometry( 0.14, 1);
var snowManHeadMat = new THREE.MeshBasicMaterial( {color: 0xf7f3dc, flatShading: true} );

//snowman scarf 
var scarfGeo = new THREE.TorusGeometry( 0.13, 0.02, 13, 50 );
var scarfMat = new THREE.MeshBasicMaterial( { color: 0xff0000 } );

//snowman hands
var handsGeo = new THREE.CylinderGeometry( 0.02, 0.02, 0.5, 10 );
var handsMat = new THREE.MeshBasicMaterial( {color: 0x6d610f} );

//snowman1's bottom part
var snowManBott1 = new THREE.Mesh (snowManBottGeo, snowManBottMat);
snowManBott1.position.x = 2.2;
snowManBott1.position.z = -2.7;
snowManBott1.position.y = 1.8;

//snowman1's head
var snowManHead1 = new THREE.Mesh (snowManHeadGeo, snowManHeadMat);
snowManHead1.position.x = 0.1;
snowManHead1.position.z = -0.12;
snowManHead1.position.y = 0.05;

//snowman1's scarf
var scarf1 = new THREE.Mesh( scarfGeo, scarfMat );
scarf1.position.z = -0.1;
scarf1.position.x = 0.08;
scarf1.position.y = 0.04;
scarf1.rotation.y = -0.7;
scarf1.rotation.x = 0.5;

//snowman1's hands
var Hands1 = new THREE.Mesh( handsGeo, handsMat );
Hands1.position.z = -0.08;
Hands1.position.x = 0.08;
Hands1.position.y = 0.04;
Hands1.rotation.x = 0.5;

//snowman2's bottom part
var snowManBott2 = new THREE.Mesh (snowManBottGeo, snowManBottMat);
snowManBott2.position.x = -1.5;
snowManBott2.position.z = -1.5;
snowManBott2.position.y = 4;
snowManBott2.rotation.y = 0.5;
snowManBott2.rotation.z = 1;

//snowman2's head
var snowManHead2 = new THREE.Mesh (snowManHeadGeo, snowManHeadMat);
snowManHead2.position.x = 0.1;
snowManHead2.position.z = -0.12;
snowManHead2.position.y = 0.05;

//snowman2's scarf
var scarf2 = new THREE.Mesh( scarfGeo, scarfMat );
scarf2.position.z = -0.1;
scarf2.position.x = 0.08;
scarf2.position.y = 0.04;
scarf2.rotation.y = -0.7;
scarf2.rotation.x = 0.5;

//snowman2's hands
var Hands2 = new THREE.Mesh( handsGeo, handsMat );
Hands2.position.z = -0.08;
Hands2.position.x = 0.08;
Hands2.position.y = 0.04;
Hands2.rotation.x = 0.5;

//plane body1
var planeBody1Geo = new THREE.BoxGeometry(0.35, 0.30, 0.25);
var planeBody1Mat = new THREE.MeshPhongMaterial({color: 0xe21414, flatShading: true});
var planeBody1 = new THREE.Mesh (planeBody1Geo, planeBody1Mat);
planeBody1.position.y = 0.15;

//plane body2
var planeBody2Geo = new THREE.BoxGeometry(0.35, 0.15, 0.23);
var planeBody2Mat = new THREE.MeshPhongMaterial({color: 0xffffff, flatShading: true});
var planeBody2 = new THREE.Mesh (planeBody2Geo, planeBody2Mat);
planeBody2.position.z = 6;
planeBody2.rotation.y = 1.5;
planeBody2.rotation.z = 2;


//plane tail
var planetailGeo = new THREE.BoxGeometry(0.15, 0.30, 0.10);
var planetailMat = new THREE.MeshPhongMaterial({color: 0xe21414, flatShading: true});
var planetail = new THREE.Mesh (planetailGeo, planetailMat);
planetail.position.y = 0.30;
planetail.position.x = 0.07;

//plane wing
var planeWingGeo = new THREE.BoxGeometry(0.20, 0.03, 0.90);
var planeWingMat = new THREE.MeshPhongMaterial({color: 0xffffff, flatShading: true});
var planeWing = new THREE.Mesh (planeWingGeo, planeWingMat);
planeWing.rotation.z = 1.57
planeWing.position.x = 0.10;
planeWing.position.y = 0.17;

//plane tail Wing
var planetailWingGeo = new THREE.BoxGeometry(0.15, 0.13, 0.03);
var planetailWingMat = new THREE.MeshPhongMaterial({color: 0xffffff, flatShading: true});
var planetailWing = new THREE.Mesh (planetailWingGeo, planetailWingMat);
planetailWing.position.x = 0.10;
planetailWing.position.y = 0.15;

//plane propeller connector
var conePropellerGeo = new THREE.ConeGeometry(0.05,0.15,10);
var conePropellerMat = new THREE.MeshPhongMaterial ({color: 0xe21414, flatShading: true});
var conePropeller = new THREE.Mesh (conePropellerGeo, conePropellerMat);
conePropeller.position.y = -0.1;
conePropeller.rotation.z = -3.1;

//plane propeller 1
var planePropellerGeo1 = new THREE.BoxGeometry(0.03,0.01,0.50);
var planePropellerMat1 = new THREE.MeshPhongMaterial ({color: 0xffffff, flatShading: true});
var planePropeller1 = new THREE.Mesh (planePropellerGeo1, planePropellerMat1);
planePropeller1.position.y = 0.01;

//plane propeller 2
var planePropellerGeo2 = new THREE.BoxGeometry(0.03,0.01,0.50);
var planePropellerMat2 = new THREE.MeshPhongMaterial ({color: 0xffffff, flatShading: true});
var planePropeller2 = new THREE.Mesh (planePropellerGeo2, planePropellerMat2);
planePropeller2.position.y = 0.03;
planePropeller2.rotation.y = 1.55;

//create shadows for objects
planeBody2.castShadow = true;
planeBody2.receiveShadow = true;
planeBody1.castShadow = true;
planeBody1.receiveShadow = true;
planetail.castShadow = true;
planetail.receiveShadow = true;
planeWing.receiveShadow = true;
earth.receiveShadow = true;
earth.castShadow = true;
land1.receiveShadow = true;
land1.castShadow = true;
land2.receiveShadow = true;
land2.castShadow = true;
land3.receiveShadow = true;
land3.castShadow = true;
land4.receiveShadow = true;
land4.castShadow = true;
land5.receiveShadow = true;
land5.castShadow = true;
volcano.receiveShadow = true;
volcano.castShadow = true;
snowManBott1.castShadow = true;
snowManBott1.receiveShadow = true;
snowManBott2.castShadow = true;
snowManBott2.receiveShadow = true;
snowManHead1.castShadow = true;
snowManHead1.receiveShadow = true;
snowManHead2.receiveShadow = true;
snowManHead2.castShadow = true;
tornado.receiveShadow = true;

// Add all meshes
//earth, sun and moon meshes
scene.add(earth);
scene.add(earth);
scene.add(sunLight);

//lands meshes
scene.add(land1);
scene.add(land2);
scene.add(land3);
scene.add(land4);
scene.add(land5);
scene.add(volcano);
scene.add(lava);

//plane meshes
scene.add(planeBody1);
scene.add(planeBody2);
scene.add(planetail);
scene.add(planeWing);
scene.add(planetailWing);
scene.add(conePropeller);
scene.add(planePropeller1);
scene.add(planePropeller2);

//trees meshes
scene.add(tree1Log);
scene.add(tree1Leaf);
scene.add(tree2Log);
scene.add(tree2Leaf);
scene.add(tree3Log);
scene.add(tree3Leaf);
scene.add(tree4Log);
scene.add(tree4Leaf);
scene.add(tree5Log);
scene.add(tree5Leaf);
scene.add(tree6Log);
scene.add(tree6Leaf);
scene.add(tree7Log);
scene.add(tree7Leaf);

//snowman meahes
scene.add(snowManBott1);
scene.add(snowManHead1);
scene.add(scarf1);
scene.add(Hands1);

scene.add(snowManBott2);
scene.add(snowManHead2);
scene.add(scarf2);
scene.add(Hands2);

//Cloud meshes 
scene.add(Cloud1M);
scene.add(Cloud1L);
scene.add(Cloud1R);
scene.add(Cloud2M);
scene.add(Cloud2L);
scene.add(Cloud2R);
scene.add(Cloud3M);
scene.add(Cloud3L);
scene.add(Cloud3R);
scene.add(Cloud4M);
scene.add(Cloud4L);
scene.add(Cloud4R);
scene.add(Cloud5M);
scene.add(Cloud5L);
scene.add(Cloud5R);
scene.add(Cloud6M);
scene.add(Cloud6L);
scene.add(Cloud6R);
scene.add(Cloud7M);
scene.add(Cloud7L);
scene.add(Cloud7R);

// ambient light
var ambient = new THREE.AmbientLight(0xffffff);
ambient.intensity = 0.40; //0.40
scene.add(ambient);

//set parents for lands
land1.parent = earth;
land2.parent = land1;
land3.parent = land2;
land4.parent = land3;
land5.parent = land4;

//set parents for volcano
volcano.parent = land3; 
lava.parent = volcano;

//set parent for tornado
tornado.parent = land1;

//set parents for tree logs and tree leafs
tree1Log.parent = land1;
tree1Leaf.parent = tree1Log;
tree2Log.parent = land1;
tree2Leaf.parent = tree2Log;
tree3Log.parent = land1;
tree3Leaf.parent = tree3Log;
tree4Log.parent = land1;
tree4Leaf.parent = tree4Log;
tree5Log.parent = land1;
tree5Leaf.parent = tree5Log;
tree6Log.parent = land1;
tree6Leaf.parent = tree6Log;
tree7Log.parent = land1;
tree7Leaf.parent = tree7Log;

//set parent for clouds
Cloud1M.parent = land1; 
Cloud1L.parent = Cloud1M; 
Cloud1R.parent = Cloud1M; 
Cloud2M.parent = land1; 
Cloud2L.parent = Cloud2M; 
Cloud2R.parent = Cloud2M; 
Cloud3M.parent = land1; 
Cloud3L.parent = Cloud3M; 
Cloud3R.parent = Cloud3M; 
Cloud4M.parent = land4; 
Cloud4L.parent = Cloud4M; 
Cloud4R.parent = Cloud4M;
Cloud5M.parent = land4; 
Cloud5L.parent = Cloud5M; 
Cloud5R.parent = Cloud5M;
Cloud6M.parent = land5; 
Cloud6L.parent = Cloud6M; 
Cloud6R.parent = Cloud6M;
Cloud7M.parent = land5; 
Cloud7L.parent = Cloud7M; 
Cloud7R.parent = Cloud7M;

//set parents for plane assests 
planeBody1.parent = planeBody2;
conePropeller.parent = planeBody2;
planePropeller1.parent = conePropeller;
planePropeller2.parent = conePropeller;
planeWing.parent = planeBody1;
planetail.parent = planeBody1; 
planetailWing.parent = planetail; 

//set parent for snowman1's parts
snowManBott1.parent = land4;
snowManHead1.parent = snowManBott1;
scarf1.parent = snowManBott1;
Hands1.parent = snowManBott1;

//set parent for snowman2's parts
snowManBott2.parent = land4;
snowManHead2.parent = snowManBott2;
scarf2.parent = snowManBott2;
Hands2.parent = snowManBott2;

//stars variables and arrays
var starsNo = 500;
var stars = [];
var sG = [];
var sM = [];
//stars
for (var i=0; i<starsNo; i++)
{
    sG.push(new THREE.SphereGeometry(0.6, 10, 10, 20 ));
    sM.push(new THREE.MeshPhongMaterial( { color: 0xFFFFFF} ));
    stars.push(new THREE.Mesh(sG[i], sM[i]));

    stars[i].position.y = Math.random()*(Math.cos(3.14)* 2500) - (Math.cos(3.14)*2000);
    stars[i].position.x = Math.random()*(Math.cos(3.14) * 2500) - (Math.cos(3.14) *2000);
    stars[i].position.z = Math.random()*(Math.cos(3.14)* 2500) - (Math.cos(3.14)*2000);
    scene.add(stars[i]);
}

//lava variable and arrays
var lavaGArray = [];
var LavaMatArray = [];
var lavaMeshArray = [];
var lavaNum = 100;
var lavaPosInitialArray = [];
var lavaDirArray = [];

//plcement of lava
for (var i=0; i<lavaNum; i++)
{
    lavaGArray.push(new THREE.SphereGeometry(0.1, 0.2, 2, 20 ));
    LavaMatArray.push(new THREE.MeshPhongMaterial({ color: 0xf96005, transparent: true, opacity: 0.3 }));
    lavaMeshArray.push(new THREE.Mesh(lavaGArray[i], LavaMatArray[i]));    

    lavaMeshArray[i].position.x = 0.1;
    lavaMeshArray[i].position.y = 0;
    lavaMeshArray[i].position.z = 0;
    lavaDirArray.push(new THREE.Vector3());
    lavaDirArray[i].x = Math.random() * 0.04 - 0.02;
    lavaDirArray[i].y = Math.random() * - 0.02 + 0.01;
    lavaDirArray[i].z = Math.random() * 0.02 + 0.01;


    lavaPosInitialArray.push(new THREE.Vector3());
    lavaPosInitialArray[i].x = lavaMeshArray[i].position.x;
    lavaPosInitialArray[i].y = lavaMeshArray[i].position.y;
    lavaPosInitialArray[i].z = lavaMeshArray[i].position.z;

    scene.add(lavaMeshArray[i]);
	lavaMeshArray[i].visible = false;
    lavaMeshArray[i].parent = lava;
}

//snow variable and arrays
var snowGeoArray = [];
var snowMatArray = [];
var snow = [];
var snowNumber = 200;
var posInitialArray = [];
var dirArray = [];

//placement of snows
for (var i=0; i<snowNumber; i++)
{
    snowGeoArray.push(new THREE.SphereGeometry(0.1, 0.1, 2, 20 ));
    snowMatArray.push(new THREE.MeshPhongMaterial({ color: 0xFFFFFF, transparent: true, opacity: 0.5 }));
    snow.push(new THREE.Mesh(snowGeoArray[i], snowMatArray[i]));


    snow[i].position.y =Math.random()*5;
    snow[i].position.x = Math.random()*6 - 4;
    snow[i].position.z = Math.random()*6 - 4;
    
    dirArray.push(new THREE.Vector3());
    dirArray[i].x = Math.random() * 0.01 - 0.02;
    dirArray[i].y = Math.random() * -0.01 - 0.005;
    dirArray[i].z = Math.random() * 0.01 - 0.02;



    posInitialArray.push(new THREE.Vector3());
    posInitialArray[i].x = snow[i].position.x;
    posInitialArray[i].y = snow[i].position.y;
    posInitialArray[i].z = snow[i].position.z;

    scene.add(snow[i]);
	snow[i].visible = false;
    snow[i].parent = land4;
}

//ray caster
var raycaster = new THREE.Raycaster();
var camDir = new THREE.Vector3();
var camPos = new THREE.Vector3();
camera.getWorldPosition(camPos);
camera.getWorldDirection(camDir);

//set position of raycaster
raycaster.set(camPos, camDir);
var laser = new THREE.ArrowHelper( raycaster.ray.direction, raycaster.ray.origin, 10, 0xffcccc, 1 );
laser.line.visible = false;
scene.add( laser ); //add to the scene

//give string name to each variable to check for intersection
land1.name = "earth";
land2.name = "earth";
land3.name = "earth";
land4.name = "earth";
land5.name = "earth";
volcano.name = "volcano";
lava.name = "volcano";
planeBody1.name = "plane";
planeBody2.name = "plane";
planeWing.name = "plane";
planetail.name = "plane";
tornado.name = "tornado";

//initialise varible iframe and degree
var iFrame = 0;
var degree = 5;

function animate() 
{
    requestAnimationFrame(animate);
    controls.update();
    // plane propeller rotations
    planePropeller1.rotation.y += 1;
    planePropeller2.rotation.y -= 1;

    // plane travel in circle
    planeBody2.position.z = Math.sin(iFrame/100 + 3.14) * 6;
    planeBody2.position.x = Math.cos(iFrame/100 + 3.14) * 6;

    // rotations of the plane during travel
    planeBody2.rotation.x = Math.cos(iFrame/100 + 3.14) * 0.5;

    // angle of the plane during orbit travelling
    planeBody2.rotation.y -= 0.01;

    //twisting effects on tornado
    if (tornado!=null) {  
        if (iFrame%200==0) { 
            degree *= -1;
            }
            twisting(tornadoGeo, degree);
    }
    
    //laser direction
    laser.setDirection(raycaster.ray.direction);

	camera.getWorldPosition(camPos);
	camera.getWorldDirection(camDir);
	
	//set position and direction of raycaster
    raycaster.set(camPos, camDir);
   
    var intersects = raycaster.intersectObjects(scene.children);
    //check for intersection
    if (intersects.length > 0) {
        //if intersect to the earth then display information
        if (intersects[0].object.name == 'earth')
        {
        document.getElementById("earthInfoL").style.visibility="visible";
        document.getElementById("sunInfoL").style.visibility="hidden";
        document.getElementById("moonInfoL").style.visibility="hidden";
        document.getElementById("earthInfoR").style.visibility="visible";
        document.getElementById("sunInfoR").style.visibility="hidden";
        document.getElementById("moonInfoR").style.visibility="hidden";
        }
        //if intersect to the sun then display information
        if (intersects[0].object.name == 'sun')
        {
        document.getElementById("sunInfoL").style.visibility="visible";
        document.getElementById("moonInfoL").style.visibility="hidden";
        document.getElementById("earthInfoL").style.visibility="hidden";
        document.getElementById("sunInfoR").style.visibility="visible";
        document.getElementById("moonInfoR").style.visibility="hidden";
        document.getElementById("earthInfoR").style.visibility="hidden";
        }
        //if intersect to the moon then display information
        if (intersects[0].object.name == 'moon')
        {
            document.getElementById("moonInfoL").style.visibility="visible";
            document.getElementById("earthInfoL").style.visibility="hidden";
            document.getElementById("sunInfoL").style.visibility="hidden";
            document.getElementById("moonInfoR").style.visibility="visible";
            document.getElementById("earthInfoR").style.visibility="hidden";
            document.getElementById("sunInfoR").style.visibility="hidden";
        }
        //if intersect to the volcano then show information
		if (intersects[0].object.name == 'volcano')
        {
            document.getElementById("volcanoInfoL").style.visibility="visible";
            document.getElementById("volcanoInfoR").style.visibility="visible";
        }
        //if intersect to the tornado then show information
		if (intersects[0].object.name == 'tornado')
        {
            document.getElementById("tornadoInfoL").style.visibility="visible";
            document.getElementById("tornadoInfoR").style.visibility="visible";
        }
        //if intersect to the plane then show information
		if (intersects[0].object.name == 'plane')
        {
            document.getElementById("planeInfoL").style.visibility="visible";
            document.getElementById("planeInfoR").style.visibility="visible";
        }

        //if intersect to the cube1 then cast "earth" animation
		if(intersects[0].object.name == 'cube1')
        {
            earth.rotation.y += 0.005;
        }

        //if intersect to the cube2 then cast "snow" animation
        if(intersects[0].object.name == 'cube2')
        {
            for (var i =0; i<snowNumber; i++)
            {
                snow[i].position.y -= 0.01;
                snow[i].position.z -=10;
                snow[i].position.x = posInitialArray[i].x + Math.sin(iFrame/100);
                if (snow[i].position.y<0)
                snow[i].position.y =Math.random()*5;
                snow[i].position.x = posInitialArray[i].x;
                snow[i].position.z = posInitialArray[i].z;
                snow[i].visible = true;
            }
        }

        //if intersect to the cube3 then cast "lava" animation
        if(intersects[0].object.name == 'cube3')
        {
            for (var i =0; i<lavaNum; i++)
            {
                lavaMeshArray[i].position.x = lavaMeshArray[i].position.x + lavaDirArray[i].x;
                lavaMeshArray[i].position.y = lavaMeshArray[i].position.y + lavaDirArray[i].y;
                lavaMeshArray[i].position.z = lavaMeshArray[i].position.z + lavaDirArray[i].z;
                if (iFrame%100 ==0)
                {
                    lavaMeshArray[i].position.x = 0.1;
                    lavaMeshArray[i].position.y = 0;
                    lavaMeshArray[i].position.z = 0;
                }
            lavaMeshArray[i].visible = true;
            }
        }
    }
    // if no intersection then hide information and objects
    else {
        document.getElementById("earthInfoL").style.visibility="hidden";
        document.getElementById("sunInfoL").style.visibility="hidden";
        document.getElementById("moonInfoL").style.visibility="hidden";
        document.getElementById("earthInfoR").style.visibility="hidden";
        document.getElementById("sunInfoR").style.visibility="hidden";
        document.getElementById("moonInfoR").style.visibility="hidden";
		for (var n =0; n<lavaNum; n++)
        {
            lavaMeshArray[n].visible = false;
        }
        for (var n =0; n<snowNumber; n++)
        {
            snow[n].visible = false;
        }
    }

    //renderer.render(scene, camera);
    effect.render(scene, camera);
    iFrame++;

}
animate();
