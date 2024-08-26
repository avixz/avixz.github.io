import { useState } from "react";
import { Canvas } from "@react-three/fiber";
import { OrbitControls } from "@react-three/drei";
import { Perf } from "r3f-perf";
import Sushi from "./Sushi";
import Plate from "./Plate";
import Chopsticks from "./Chopsticks";
import Wip from "./Wip";

export default function App() {
  const [showWip, setShowWip] = useState(false);
  const toggleWip = () => setShowWip(!showWip);

  return (
    <>
      <Canvas camera={{ position: [4, 5, 7] }}>
        {showWip && <Perf position="top-left" />}

        <color attach="background" args={[0.05, 0.05, 0.05]} />

        <OrbitControls makeDefault />

        <directionalLight position={[1, 2, 3]} intensity={3.5} />
        <ambientLight intensity={1} />

        <Sushi />
        <Plate />
        <Chopsticks />
      </Canvas>
      <Wip show={showWip} toggle={toggleWip} disabled />
    </>
  );
}
