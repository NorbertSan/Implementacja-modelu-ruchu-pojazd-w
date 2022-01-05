import React from "react";

const ErrorPage = ({ error }) => {
  return <pre>{JSON.stringify(error, null, 2)}</pre>;
};

export default ErrorPage;
