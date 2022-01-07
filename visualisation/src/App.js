import styles from "./App.module.scss";
import Board from "./components/Board/Board";
import ErrorPage from "./components/ErrorPage/ErrorPage";
import useGenerateNewCars from "./hooks/useGenerateNewCars";
import useUpdatePositions from "./hooks/useUpdatePositions";
import useGetGlobals from "./hooks/useGetGlobals";
import useInitBoardModule from "./hooks/useInitBoardModule";
import useGenerateNewCarsOnKeyStroke from "./hooks/useGenerateNewCarsOnKeyStroke";
import ConfigurationDashboard from "./components/ConfigurationDashboard/ConfigurationDashboard";
import { useState } from "react";
import StatisticsDashboard from "./components/StatisticsDashboard/StatisticsDashboard";

const App = () => {
  const [simulationStatus, setSimulationStatus] = useState(true);

  const { error, WasmModule, loading, boardObject, roadVector } =
    useInitBoardModule();
  const { boardSize, indexDirectionClassDict, middleCellIndexes } =
    useGetGlobals(WasmModule);
  const { boardOccupancyVector, updatesAmount, currentCarsAmount } =
    useUpdatePositions(boardObject, WasmModule, simulationStatus);
  const { generatedCarsAmount, generatedCarsPerRoute } =
    useGenerateNewCars(boardObject);

  useGenerateNewCarsOnKeyStroke(boardObject, simulationStatus);

  const toggleSimulationStatus = () => setSimulationStatus(!simulationStatus);

  return (
    <main className={styles.main}>
      {error && <ErrorPage error={error} />}
      {loading && <span>Loading...</span>}

      {!error && !loading && (
        <>
          <section className={styles["dashboards-wrapper"]}>
            <ConfigurationDashboard
              simulationStatus={simulationStatus}
              toggleSimulationStatus={toggleSimulationStatus}
              WasmModule={WasmModule}
            />
            <StatisticsDashboard
              generatedCarsPerRoute={generatedCarsPerRoute}
              currentCarsAmount={currentCarsAmount}
              generatedCarsAmount={generatedCarsAmount}
              updatesAmount={updatesAmount}
            />
          </section>
          <Board
            boardSize={boardSize}
            roadVector={roadVector}
            boardOccupancyVector={boardOccupancyVector}
            indexDirectionClassDict={indexDirectionClassDict}
            middleCellIndexes={middleCellIndexes}
          />
        </>
      )}
    </main>
  );
};

export default App;
