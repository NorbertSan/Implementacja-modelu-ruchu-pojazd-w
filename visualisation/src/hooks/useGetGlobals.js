import { useEffect, useState } from "react";

const useGetGlobals = (WasmModule) => {
  const [boardSize, setBoardSize] = useState(null);
  const [middleCellIndexes, setMiddleCellIndexes] = useState(null);

  const [indexDirectionClassDict, setIndexDirectionClassDict] = useState({});

  useEffect(() => {
    if (!WasmModule) return;

    setBoardSize(WasmModule.get_board_size());

    const indexForDownDirectionIcon =
      WasmModule.get_index_for_down_direction_icon();
    const indexForDownRightDirectionIcon =
      WasmModule.get_index_for_down_right_direction_icon();
    const indexForUpDirectionIcon =
      WasmModule.get_index_for_up_direction_icon();
    const indexForUpRightDirectionIcon =
      WasmModule.get_index_for_up_right_direction_icon();
    const indexForRightDirectionIcon =
      WasmModule.get_index_for_right_direction_icon();
    const indexForRightRightDirectionIcon =
      WasmModule.get_index_for_right_right_direction_icon();
    const indexForLeftDirectionIcon =
      WasmModule.get_index_for_left_direction_icon();
    const indexForLeftRightDirectionIcon =
      WasmModule.get_index_for_left_right_direction_icon();

    setIndexDirectionClassDict({
      [indexForDownDirectionIcon]: "down_direction",
      [indexForDownRightDirectionIcon]: "down_right_direction",
      [indexForUpDirectionIcon]: "up_direction",
      [indexForUpRightDirectionIcon]: "up_right_direction",
      [indexForRightDirectionIcon]: "right_direction",
      [indexForRightRightDirectionIcon]: "right_right_direction",
      [indexForLeftDirectionIcon]: "left_direction",
      [indexForLeftRightDirectionIcon]: "left_right_direction",
    });

    setMiddleCellIndexes(WasmModule.get_middle_cell_indexes());
  }, [WasmModule]);

  return {
    boardSize,
    indexDirectionClassDict,
    middleCellIndexes,
  };
};

export default useGetGlobals;
