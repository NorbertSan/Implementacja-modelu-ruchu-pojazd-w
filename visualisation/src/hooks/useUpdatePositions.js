import { useEffect, useRef, useState } from "react";

const useUpdatePositions = (
  boardObject,
  WasmModule,
  simulationStatus,
  simulationOneRoundIntervalTime,
  hasSimulationFinished
) => {
  const [boardOccupancyVector, setBoardOccupancyVector] = useState([]);
  const [updatesAmount, setUpdatesAmount] = useState(0);
  const [currentCarsAmount, setCurrentCarsAmount] = useState(0);
  const [currentCarsAmountStatistics, setCurrentCarsAmountStatistics] =
    useState([]);

  const intervalRef = useRef(null);

  const setUpdatePositionsInterval = () => {
    let updatesAmountTemp = updatesAmount;

    const currentAmountTemp = [];

    const interval = setInterval(() => {
      boardObject.update_positions();
      setBoardOccupancyVector(boardObject.get_occupied_board());

      const currentAmount = boardObject.get_current_cars_amount();
      currentAmountTemp.push(currentAmount);
      setCurrentCarsAmount(currentAmount);

      setCurrentCarsAmountStatistics(currentAmountTemp);

      updatesAmountTemp++;
      setUpdatesAmount(updatesAmountTemp);

      const error = WasmModule.get_error();
      if (error) console.error(error);
    }, simulationOneRoundIntervalTime);
    intervalRef.current = interval;
  };

  const clearUpdatePositionsInterval = () => {
    if (intervalRef.current) {
      clearInterval(intervalRef.current);
      intervalRef.current = null;
    }
  };

  useEffect(() => {
    if (!boardObject) return;
    setUpdatePositionsInterval();

    return () => clearUpdatePositionsInterval();
  }, [boardObject]);

  useEffect(() => {
    if (
      !boardObject ||
      (intervalRef.current && simulationStatus) ||
      (!intervalRef.current && !simulationStatus)
    )
      return;

    if (!simulationStatus) clearUpdatePositionsInterval();

    if (simulationStatus) setUpdatePositionsInterval();
  }, [simulationStatus]);

  useEffect(() => {
    if (!boardObject) return;

    clearUpdatePositionsInterval();
    setUpdatePositionsInterval();
  }, [simulationOneRoundIntervalTime]);

  useEffect(() => {
    if (!boardObject || !hasSimulationFinished) return;

    console.log(currentCarsAmountStatistics.join(";"));
    clearUpdatePositionsInterval();
  }, [hasSimulationFinished]);

  return { boardOccupancyVector, updatesAmount, currentCarsAmount };
};

export default useUpdatePositions;
