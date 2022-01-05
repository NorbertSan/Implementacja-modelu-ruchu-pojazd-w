import styles from "./App.module.scss";
import Board from "./components/Board/Board";
import ErrorPage from "./components/ErrorPage/ErrorPage";
import useGenerateNewCars from "./hooks/useGenerateNewCars";
import useUpdatePositions from "./hooks/useUpdatePositions";
import useGetGlobals from "./hooks/useGetGlobals";
import useInitBoardModule from "./hooks/useInitBoardModule";
import useGenerateNewCarsOnKeyStroke from "./hooks/useGenerateNewCarsOnKeyStroke";

const App = () => {
  const { error, WasmModule, loading, boardObject, roadVector } =
    useInitBoardModule();
  const { boardSize, indexDirectionClassDict, middleCellIndexes } =
    useGetGlobals(WasmModule);
  const { boardOccupancyVector } = useUpdatePositions(boardObject, WasmModule);
  // useGenerateNewCars(boardObject);

  useGenerateNewCarsOnKeyStroke(boardObject);

  return (
    <main className={styles.main}>
      {error && <ErrorPage error={error} />}
      {loading && <span>Loading...</span>}

      {!error && !loading && (
        <Board
          boardSize={boardSize}
          roadVector={roadVector}
          boardOccupancyVector={boardOccupancyVector}
          indexDirectionClassDict={indexDirectionClassDict}
          middleCellIndexes={middleCellIndexes}
        />
      )}
    </main>
  );
};

export default App;
