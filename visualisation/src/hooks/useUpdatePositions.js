import { useEffect, useRef, useState } from "react";
import { SIMULATION_UPDATE_TIME_INTERVAL } from "../constants/timers";

const useUpdatePositions = (boardObject, WasmModule, simulationStatus) => {
  const [boardOccupancyVector, setBoardOccupancyVector] = useState([]);
  const [updatesAmount, setUpdatesAmount] = useState(0);
  const [currentCarsAmount, setCurrentCarsAmount] = useState(0);

  const intervalRef = useRef(null);

  const setUpdatePositionsInterval = () => {
    let updatesAmountTemp = updatesAmount;

    const interval = setInterval(() => {
      boardObject.update_positions();
      setBoardOccupancyVector(boardObject.get_occupied_board());
      setCurrentCarsAmount(boardObject.get_current_cars_amount());

      updatesAmountTemp++;
      setUpdatesAmount(updatesAmountTemp);

      const error = WasmModule.get_error();
      if (error) console.error(error);
    }, SIMULATION_UPDATE_TIME_INTERVAL);
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

  return { boardOccupancyVector, updatesAmount, currentCarsAmount };
};

export default useUpdatePositions;
