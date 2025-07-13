export class LoggerFactory {
  /**
   * Construct a logger for an OAuth component (e.g., client, auth-server).
   *
   * @param component Name of the OAuth component, e.g., "CLIENT", "AUTH-SERVER".
   * @param char Delimiter line character.
   * @param width Width of delimiter lines.
   */
  constructor(
    private component: string,
    private char: string = '=',
    private width: number = 80
  ) {}

  loggerForEndpoint(endpoint: string): Logger {
    return new Logger(this.component, endpoint, this.char, this.width);
  }
}

class Logger {
  /**
   * Construct a logger for an OAuth component (e.g., client, auth-server).
   *
   * @param component Name of the OAuth component, e.g., "CLIENT", "AUTH-SERVER".
   * @param endpoint API endpoint within the component (without "/", e.g., "authorize", "callback").
   * @param char Delimiter line character.
   * @param width Width of delimiter lines.
   */
  constructor(
    private component: string,
    private endpoint: string,
    private char: string = '=',
    private width: number = 80
  ) {}

  /**
   * Logs the beginning of a delimiter line to the console.
   */
  logDelimiterBegin() {
    const titleWithSpaces = ` ${this.component.toUpperCase()} `;
    const sideLength = Math.max(0, Math.floor((this.width - titleWithSpaces.length) / 2));
    const left = this.char.repeat(sideLength);
    const right = this.char.repeat(this.width - sideLength - titleWithSpaces.length);
    console.log(`${left}${titleWithSpaces}${right}\n`);
  }

  /**
   * Logs the end of a delimiter line to the console.
   */
  logDelimiterEnd() {
    console.log(`${this.char.repeat(this.width)}\n`);
  }

  /**
   * Log a step with a step number, component, endpoint and message in format "[COMPONENT] step x.y (ENDPOINT): message".
   *
   * @param step Step number, can be either only major number (e.g., "2") or major.minor (e.g., "2.5", "3.12").
   * @param message Message following the step number.
   */
  logStep(step: number, message: string) {
    const major = Math.floor(step);
    const minor = Math.round((step - major) * 10);
    if (Math.floor(minor) !== minor) {
      throw Error(
        `Step number "${step}" is not supported, only single-digit minor step number is supported.`
      );
    }
    const stepStr = minor > 0 ? `${major}.${minor}` : `${major}`;
    console.log(`[${this.component}/${this.endpoint}] Step ${stepStr}: ${message}\n`);
  }
}
