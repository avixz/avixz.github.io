import { Canvas } from "@react-three/fiber";
import PineTree from "./PineTree";

function App() {
  return (
    <>
      <Canvas camera={{ position: [4, 5, 7] }}>
        <directionalLight position={[1, 2, 3]} intensity={3.5} />
        <ambientLight intensity={1} />

        <PineTree />
      </Canvas>
    </>
  );
}

export default App;
