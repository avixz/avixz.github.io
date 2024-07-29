import { useGLTF } from "@react-three/drei";

export default function Plate() {
  const model = useGLTF("./PineTree.glb");

  return <primitive object={model.scene} />;
}
