import { useEffect, useState } from "react";
import styles from "./Board.module.scss";
import classnames from "classnames";
import { ReactComponent as CarSvg } from "../../assets/icons/car.svg";
import { isElementInVector } from "../../helpers/vector-helpers";

const createBoardGridStyles = (boardSize) => ({
  display: "grid",
  gridTemplateColumns: `repeat(${boardSize}, 1fr)`,
  gridTemplateRows: `repeat(${boardSize}, 1fr)`,
});

const Board = ({
  boardSize,
  roadVector,
  boardOccupancyVector,
  indexDirectionClassDict,
  middleCellIndexes,
}) => {
  const [boardGridStyles, setBoardGridStyles] = useState();
  const [cells, setCells] = useState([]);

  useEffect(() => {
    // Create grid styles based on board size
    if (!boardSize) return;

    setBoardGridStyles(createBoardGridStyles(boardSize));
  }, [boardSize]);

  useEffect(() => {
    // Cells initialization based on road vectors
    const boardCells = [];
    for (let i = 0; i < boardSize * boardSize; i++) {
      const directionClass = indexDirectionClassDict[i];
      const className = classnames({
        [styles.road]: Boolean(roadVector.get(i)),
        [styles.middle_cell]: isElementInVector(middleCellIndexes, i),
        [styles.no_road]: !Boolean(roadVector.get(i)),
        [styles[directionClass]]: styles[directionClass],
        [styles.main_road]:
          process.env.REACT_APP_CROSSROAD_VERSION == 1 &&
          (i === 252 || i === 618),
        [styles.yield_road]:
          process.env.REACT_APP_CROSSROAD_VERSION == 1 &&
          (i === 350 || i === 520),
        [styles.equal_crossroad]:
          process.env.REACT_APP_CROSSROAD_VERSION == 2 &&
          (i === 252 || i === 618 || i === 350 || i === 520),
      });

      boardCells.push(<div id={i} key={i} className={className} />);
    }
    setCells(boardCells);
  }, [roadVector, middleCellIndexes]);

  useEffect(() => {
    // Updating cells based on boardOccupancyVector
    if (cells.length === 0 || !boardOccupancyVector) return;

    setCells(
      cells.map((cellDiv, index) => {
        return {
          ...cellDiv,
          props: {
            ...cellDiv.props,

            children: [
              Boolean(boardOccupancyVector.get(index)) ? (
                <CarSvg key={`car-${index}`} className={styles.icon} />
              ) : null,
            ],
          },
        };
      })
    );
  }, [boardOccupancyVector]);

  return (
    <div style={boardGridStyles} className={styles.board}>
      {cells}
    </div>
  );
};

export default Board;
