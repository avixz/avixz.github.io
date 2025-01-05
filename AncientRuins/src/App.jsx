import { Canvas } from "@react-three/fiber";
import { OrbitControls } from "@react-three/drei";

import AncientRuins from "./AncientRuins";

function App() {
  return (
    <>
      <Canvas camera={{ position: [4, 5, 7] }}>
        <color attach="background" args={[0.05, 0.05, 0.05]} />

        <OrbitControls />

        <AncientRuins />
      </Canvas>
    </>
  );
}

export default App;
