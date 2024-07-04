import { useGLTF } from "@react-three/drei";

export default function Chopsticks() {
  const model = useGLTF("./Chopsticks.glb");

  return <primitive object={model.scene} />;
}
