import { useGLTF } from "@react-three/drei";

export default function Sushi() {
  const model = useGLTF("./Sushi.glb");

  return <primitive object={model.scene} />;
}
