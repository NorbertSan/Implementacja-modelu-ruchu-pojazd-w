import { useState } from "react";

import styles from "./App.module.scss";
import Board from "./components/Board/Board";
import ConfigurationDashboard from "./components/ConfigurationDashboard/ConfigurationDashboard";
import ErrorPage from "./components/ErrorPage/ErrorPage";
import StatisticsDashboard from "./components/StatisticsDashboard/StatisticsDashboard";
import { SIMULATION_UPDATE_TIME_INTERVAL } from "./constants/timers";
import useGenerateNewCars from "./hooks/useGenerateNewCars";
import useGetGeneratedCarsStatistics from "./hooks/useGetGeneratedCarsStatistics";
import useGetGlobals from "./hooks/useGetGlobals";
import useInitBoardModule from "./hooks/useInitBoardModule";
import useUpdatePositions from "./hooks/useUpdatePositions";

const App = () => {
  const [hasSimulationFinished, setHasSimulationFinished] = useState(false);
  const [simulationStatus, setSimulationStatus] = useState(true);
  const [simulationOneRoundIntervalTime, setSimulationOneRoundIntervalTime] =
    useState(SIMULATION_UPDATE_TIME_INTERVAL);

  const { error, WasmModule, loading, boardObject, roadVector } =
    useInitBoardModule();
  const { boardSize, indexDirectionClassDict, middleCellIndexes } =
    useGetGlobals(WasmModule);
  const { boardOccupancyVector, updatesAmount, currentCarsAmount } =
    useUpdatePositions(
      boardObject,
      WasmModule,
      simulationStatus,
      simulationOneRoundIntervalTime,
      hasSimulationFinished
    );
  const { generatedCarsAmount, generatedCarsPerRoute } =
    useGetGeneratedCarsStatistics(boardObject);

  useGenerateNewCars(
    boardObject,
    simulationStatus,
    generatedCarsPerRoute,
    setHasSimulationFinished,
    hasSimulationFinished,
    currentCarsAmount
  );

  const toggleSimulationStatus = () => {
    setSimulationStatus(!simulationStatus);
    boardObject.set_simulation_status(!simulationStatus);
  };

  return (
    <main className={styles.main}>
      {error && <ErrorPage error={error} />}
      {loading && <span>Loading...</span>}

      {!error && !loading && (
        <>
          <section className={styles["dashboards-wrapper"]}>
            <ConfigurationDashboard
              hasSimulationFinished={hasSimulationFinished}
              simulationStatus={simulationStatus}
              toggleSimulationStatus={toggleSimulationStatus}
              simulationOneRoundIntervalTime={simulationOneRoundIntervalTime}
              setSimulationOneRoundIntervalTime={
                setSimulationOneRoundIntervalTime
              }
              WasmModule={WasmModule}
            />
            <StatisticsDashboard
              hasSimulationFinished={hasSimulationFinished}
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
