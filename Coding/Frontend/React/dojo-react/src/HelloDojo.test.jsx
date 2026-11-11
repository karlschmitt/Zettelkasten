import { render, screen } from "@testing-library/react";
import HelloDojo from "./HelloDojo";

test("greets the dojo", () => {
  render(<HelloDojo />);
  expect(screen.getByText("Hello, Dojo!")).toBeInTheDocument();
});
