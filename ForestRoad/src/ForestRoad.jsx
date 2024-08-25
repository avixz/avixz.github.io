import { useGLTF } from "@react-three/drei";

export default function ForestRoad() {
  const model = useGLTF("./ForestRoad.glb");

  return (
    <>
      <primitive object={model.scene} />;
    </>
  );
}
