import { useEffect, useRef, useState } from "react";
import { SIMULATION_UPDATE_TIME_INTERVAL } from "../constants/timers";

const useUpdatePositions = (boardObject, WasmModule) => {
  const [boardOccupancyVector, setBoardOccupancyVector] = useState([]);
  const intervalRef = useRef(null);

  const setUpdatePositionsInterval = () => {
    const interval = setInterval(() => {
      boardObject.update_positions();
      setBoardOccupancyVector(boardObject.get_occupied_board());

      const error = WasmModule.get_error();
      if (error) console.error(error);
    }, SIMULATION_UPDATE_TIME_INTERVAL);
    intervalRef.current = interval;
  };

  const clearUpdatePositionsInterval = () => {
    clearInterval(intervalRef.current);
    intervalRef.current = null;
  };

  useEffect(() => {
    if (!boardObject) return;
    setUpdatePositionsInterval();

    return () => clearUpdatePositionsInterval();
  }, [boardObject]);

  useEffect(() => {
    if (!boardObject) return;

    boardObject.get_occupied_board();
  }, [boardObject]);

  return { boardOccupancyVector };
};

export default useUpdatePositions;
