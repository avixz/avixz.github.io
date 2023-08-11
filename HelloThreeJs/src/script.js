import * as THREE from "three";
import { OrbitControls } from "three/examples/jsm/controls/OrbitControls";
import { FontLoader } from "three/examples/jsm/loaders/FontLoader";
import { TextGeometry } from "three/examples/jsm/geometries/TextGeometry";

// Textures
THREE.ColorManagement.enabled = false;
const loadingManager = new THREE.LoadingManager();
loadingManager.onProgress = (url) => {
  console.log("Loading file: ", url);
};
const textureLoader = new THREE.TextureLoader(loadingManager);
const doorColorTexture = textureLoader.load("textures/door/color.jpg");
const matcapTexture = textureLoader.load("textures/matcaps/1.png");

// Fonts
const fontLoader = new FontLoader(loadingManager);
fontLoader.load("fonts/helvetiker_regular.typeface.json", (font) => {
  const textGeometry = new TextGeometry("Hello, Three.js!", {
    font: font,
    size: 0.5,
    height: 0.2,
    curveSegments: 5,
    bevelEnabled: true,
    bevelThickness: 0.03,
    bevelSize: 0.02,
    bevelOffset: 0,
    bevelSegments: 4,
  });
  textGeometry.center();
  textGeometry.computeBoundingBox();
  console.log(textGeometry.boundingBox);

  const material = new THREE.MeshMatcapMaterial({ matcap: matcapTexture });
  const text = new THREE.Mesh(textGeometry, material);
  scene.add(text);

  const donutGeometry = new THREE.TorusGeometry(0.3, 0.2, 20, 45);

  for (let i = 0; i < 100; i++) {
    const donut = new THREE.Mesh(donutGeometry, material);

    donut.position.x = (Math.random() - 0.5) * 10;
    donut.position.y = (Math.random() - 0.5) * 10;
    donut.position.z = (Math.random() - 0.5) * 10;

    donut.rotation.x = Math.random() * Math.PI;
    donut.rotation.y = Math.random() * Math.PI;

    const scale = Math.random();
    donut.scale.set(scale, scale, scale);

    scene.add(donut);
  }
});

// Cursor
const cursor = {
  x: 0,
  y: 0,
};
window.addEventListener("mousemove", (event) => {
  cursor.x = event.clientX / sizes.width - 0.5;
  cursor.y = -(event.clientY / sizes.height - 0.5);
});

// Canvas
const canvas = document.querySelector(".webgl");

// Scene
const scene = new THREE.Scene();

// Objects
const cube = new THREE.Mesh(
  new THREE.BoxGeometry(1, 1, 1),
  new THREE.MeshBasicMaterial({ map: doorColorTexture })
);
cube.position.y = -1;

scene.add(cube);

// Lights
const ambientLight = new THREE.AmbientLight(0xffffff, 0.5);
scene.add(ambientLight);

const pointLight = new THREE.PointLight(0xffffff, 0.5);
pointLight.position.x = 2;
pointLight.position.y = 2;
pointLight.position.z = 2;
scene.add(pointLight);

// Sizes
const sizes = {
  width: window.innerWidth,
  height: window.innerHeight,
};

window.addEventListener("resize", () => {
  // Update sizes
  sizes.width = window.innerWidth;
  sizes.height = window.innerHeight;

  // Update camera
  camera.aspect = sizes.width / sizes.height;
  camera.updateProjectionMatrix();

  // Update renderer
  renderer.setSize(sizes.width, sizes.height);
  renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
});

window.addEventListener("dblclick", () => {
  if (!document.fullscreenElement) {
    canvas.requestFullscreen();
  } else {
    document.exitFullscreen();
  }
});

// Camera
const camera = new THREE.PerspectiveCamera(
  45,
  sizes.width / sizes.height,
  0.1,
  100
);

scene.add(camera);

// Controls
const controls = new OrbitControls(camera, canvas);
controls.enableDamping = true;

// Renderer
const renderer = new THREE.WebGLRenderer({
  canvas: canvas,
});
renderer.outputColorSpace = THREE.LinearSRGBColorSpace;
camera.position.set(0, 0, 5);

// Clock
const clock = new THREE.Clock();

renderer.setSize(sizes.width, sizes.height);
renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));

// Animations
const tick = () => {
  // Clock
  const elapsedTime = clock.getElapsedTime();

  // Update objects
  cube.rotation.y = 0.1 * elapsedTime;

  cube.rotation.x = 0.15 * elapsedTime;

  // Update controls
  controls.update();

  // Render
  renderer.render(scene, camera);
  window.requestAnimationFrame(tick);
};
tick();
