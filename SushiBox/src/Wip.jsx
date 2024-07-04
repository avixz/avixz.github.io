export default function Wip({ show, toggle, disabled }) {
  return (
    <>
      {show && (
        <div className="docs">
          <iframe className="docs" src="./docs.html" />
        </div>
      )}
      {disabled || (
        <button className="docsButton" onClick={toggle}>
          WIP
        </button>
      )}
    </>
  );
}
