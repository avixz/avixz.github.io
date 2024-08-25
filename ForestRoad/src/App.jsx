import { Canvas } from "@react-three/fiber";
import { OrbitControls } from "@react-three/drei";

import ForestRoad from "./ForestRoad";

function App() {
  return (
    <>
      <Canvas camera={{ position: [4, 5, 7] }}>
        <OrbitControls minPolarAngle={0} />
        <OrbitControls maxPolarAngle={Math.PI / 3} />

        <directionalLight position={[1, 2, 3]} intensity={3.5} />
        <ambientLight intensity={1} />

        <ForestRoad />
      </Canvas>
    </>
  );
}

export default App;
