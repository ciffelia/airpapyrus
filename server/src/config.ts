if (process.env.PORT == null) {
  throw new Error('PORT is not set.')
}
export const port = parseInt(process.env.PORT)

if (process.env.DB_PATH == null) {
  throw new Error('DB_PATH is not set.')
}
export const dbPath = process.env.DB_PATH
