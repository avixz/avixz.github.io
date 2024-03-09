import { useGLTF } from "@react-three/drei";

export default function Plate() {
  const model = useGLTF("./Plate.glb");

  return <primitive object={model.scene} />;
}
