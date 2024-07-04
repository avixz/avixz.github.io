import { useState } from "react";
import { Canvas } from "@react-three/fiber";
import { OrbitControls } from "@react-three/drei";
import { Perf } from "r3f-perf";
import Sushi from "./Sushi";
import Plate from "./Plate";
import Wip from "./Wip";

export default function Game() {
  const [showWip, setShowWip] = useState(false);
  const toggleWip = () => setShowWip(!showWip);

  return (
    <>
      <Canvas camera={{ position: [4, 5, 7] }}>
        {showWip && <Perf position="top-left" />}

        <OrbitControls makeDefault />

        <directionalLight position={[1, 2, 3]} intensity={3.5} />
        <ambientLight intensity={1} />

        <Sushi />
        <Plate />
        <Plate />
      </Canvas>
      <Wip show={showWip} toggle={toggleWip} disabled />
    </>
  );
}
