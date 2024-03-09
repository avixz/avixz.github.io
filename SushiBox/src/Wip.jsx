export default function Wip({ show, toggle }) {
  return (
    <>
      {show && (
        <div className="docs">
          <iframe className="docs" src="./docs.html" />
        </div>
      )}
      <button className="docsButton" onClick={toggle}>
        WIP
      </button>
    </>
  );
}
