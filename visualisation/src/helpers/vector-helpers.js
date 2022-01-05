export const isElementInVector = (vector, element) => {
  const arr = [];
  for (let i = 0; i < vector.size(); i++) {
    arr.push(vector.get(i));
  }

  return arr.includes(element);
};
