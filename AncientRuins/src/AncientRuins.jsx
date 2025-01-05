import { useGLTF, useTexture } from "@react-three/drei";
import { MeshBasicMaterial, SRGBColorSpace } from "three";

export default function AncientRuins() {
  const model = useGLTF("./AncientRuins.glb");
  const bakedTexture = useTexture("./baked.jpg");
  const bakedMaterial = new MeshBasicMaterial({ map: bakedTexture });

  bakedTexture.flipY = false;
  bakedTexture.colorSpace = SRGBColorSpace;

  model.scene.children.forEach((child) => console.log(child.name));

  const baked = model.scene.children.find((child) => child.name === "baked");
  baked.material = bakedMaterial;

  return (
    <>
      <primitive object={model.scene} />
    </>
  );
}
